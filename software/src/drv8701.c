/* performance-dc-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * drv8701.c: Driver for DRV8701
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "drv8701.h"
#include "configs/config_drv8701.h"

#include "voltage.h"
#include "communication.h"

#include "bricklib2/hal/ccu4_pwm/ccu4_pwm.h"
#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/logging/logging.h"
#include "bricklib2/utility/util_definitions.h"

#include "xmc_gpio.h"

DRV8701 drv8701;

const XMC_GPIO_CONFIG_t input_pullup_config = {
	.mode             = XMC_GPIO_MODE_INPUT_PULL_UP,
	.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
};

const XMC_GPIO_CONFIG_t input_default_config = {
	.mode             = XMC_GPIO_MODE_INPUT_TRISTATE,
	.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
};

const XMC_GPIO_CONFIG_t output_high_config = {
	.mode         = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
	.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH
};

const XMC_GPIO_CONFIG_t output_low_config = {
	.mode         = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
	.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW
};

void drv8701_init(void) {
	memset(&drv8701, 0, sizeof(DRV8701));

	XMC_GPIO_Init(DRV8701_NSLEEP_PIN,    &output_low_config);
	XMC_GPIO_Init(DRV8701_LED_CW_PIN,    &output_high_config);
	XMC_GPIO_Init(DRV8701_LED_CCW_PIN,   &output_high_config);
	XMC_GPIO_Init(DRV8701_LED_ERROR_PIN, &output_high_config);
	XMC_GPIO_Init(DRV8701_NFAULT_PIN,    &input_default_config);
	XMC_GPIO_Init(DRV8701_SNSOUT_PIN,    &input_default_config);

	ccu4_pwm_init(DRV8701_IN1_PIN, DRV8701_IN1_SLICE, 3200 - 1);
	ccu4_pwm_init(DRV8701_IN2_PIN, DRV8701_IN2_SLICE, 3200 - 1);

	drv8701.cw_led_flicker_state.config    = PERFORMANCE_DC_CW_LED_CONFIG_SHOW_CW_AS_FORWARD;
	drv8701.ccw_led_flicker_state.config   = PERFORMANCE_DC_CCW_LED_CONFIG_SHOW_CCW_AS_BACKWARD;
	drv8701.error_led_flicker_state.config = PERFORMANCE_DC_ERROR_LED_CONFIG_SHOW_ERROR;

	drv8701.acceleration  = 10000;
	drv8701.deceleration  = 10000;
	drv8701.pwm_frequency = 20000;

	drv8701.thermal_shutdown_temperature = 125;
	drv8701.cb_emergency_shutdown_enabled = true; // Emergency shutdown callback is enabled by default
}

static void drv8701_handle_error_led(const uint32_t t) {
	static uint32_t last_time = 0;

	if(drv8701.error_led_flicker_state.config == PERFORMANCE_DC_ERROR_LED_CONFIG_SHOW_HEARTBEAT) {
		led_flicker_tick(&drv8701.error_led_flicker_state, t, DRV8701_LED_ERROR_PIN);
	} else if(drv8701.cw_led_flicker_state.config == PERFORMANCE_DC_CW_LED_CONFIG_ON) {
		XMC_GPIO_SetOutputLow(DRV8701_LED_ERROR_PIN);
	} else if(drv8701.cw_led_flicker_state.config == PERFORMANCE_DC_CW_LED_CONFIG_OFF) {
		XMC_GPIO_SetOutputHigh(DRV8701_LED_ERROR_PIN);
	} else if(drv8701.error_led_flicker_state.config == PERFORMANCE_DC_ERROR_LED_CONFIG_SHOW_ERROR) {
		uint32_t error = 0;
		if(voltage.voltage < 6000) {
			error = 500;
		}

		if(!XMC_GPIO_GetInput(DRV8701_NFAULT_PIN)) {
			error = 125;
		}

		if(error == 0) {
			XMC_GPIO_SetOutputHigh(DRV8701_LED_ERROR_PIN);
		} else {
			if(system_timer_is_time_elapsed_ms(last_time, error)) {
				XMC_GPIO_ToggleOutput(DRV8701_LED_ERROR_PIN);
				last_time = system_timer_get_ms();
			}
		}
	}
}

static void drv8701_handle_cw_led(const uint32_t t) {
	bool led_on = false;

	if(drv8701.cw_led_flicker_state.config == PERFORMANCE_DC_CW_LED_CONFIG_SHOW_HEARTBEAT) {
		led_flicker_tick(&drv8701.cw_led_flicker_state, t, DRV8701_LED_CW_PIN);
		return;
	} else if(drv8701.cw_led_flicker_state.config == PERFORMANCE_DC_CW_LED_CONFIG_ON) {
		led_on = true;
	} else if(drv8701.cw_led_flicker_state.config == PERFORMANCE_DC_CW_LED_CONFIG_OFF) {
		led_on = false;
	} else if(!drv8701.enabled) {
		led_on = false;
	} else {
		if(drv8701.velocity == 0) {
			led_on = false;
		} else if(drv8701.velocity < 0) {
			if(drv8701.cw_led_flicker_state.config == PERFORMANCE_DC_CW_LED_CONFIG_SHOW_CW_AS_FORWARD) {
				led_on = false;
			} else {
				led_on = true;
			}
		} else {
			if(drv8701.cw_led_flicker_state.config == PERFORMANCE_DC_CW_LED_CONFIG_SHOW_CW_AS_FORWARD) {
				led_on = true;
			} else {
				led_on = false;
			}
		}
	}

	if(led_on) {
		XMC_GPIO_SetOutputLow(DRV8701_LED_CW_PIN);
	} else {
		XMC_GPIO_SetOutputHigh(DRV8701_LED_CW_PIN);
	}
}

static void drv8701_handle_ccw_led(const uint32_t t) {
	bool led_on = false;

	if(drv8701.ccw_led_flicker_state.config == PERFORMANCE_DC_CCW_LED_CONFIG_SHOW_HEARTBEAT) {
		led_flicker_tick(&drv8701.ccw_led_flicker_state, t, DRV8701_LED_CCW_PIN);
		return;
	} else if(drv8701.ccw_led_flicker_state.config == PERFORMANCE_DC_CCW_LED_CONFIG_ON) {
		led_on = true;
	} else if(drv8701.ccw_led_flicker_state.config == PERFORMANCE_DC_CCW_LED_CONFIG_OFF) {
		led_on = false;
	} else if(!drv8701.enabled) {
		led_on = false;
	} else {
		if(drv8701.velocity == 0) {
			led_on = false;
		} else if(drv8701.velocity < 0) {
			if(drv8701.ccw_led_flicker_state.config == PERFORMANCE_DC_CCW_LED_CONFIG_SHOW_CCW_AS_FORWARD) {
				led_on = false;
			} else {
				led_on = true;
			}
		} else {
			if(drv8701.ccw_led_flicker_state.config == PERFORMANCE_DC_CCW_LED_CONFIG_SHOW_CCW_AS_FORWARD) {
				led_on = true;
			} else {
				led_on = false;
			}
		}
	}

	if(led_on) {
		XMC_GPIO_SetOutputLow(DRV8701_LED_CCW_PIN);
	} else {
		XMC_GPIO_SetOutputHigh(DRV8701_LED_CCW_PIN);
	}
}

void drv8701_tick_update_frequency(void) {
	// Frequency between 1000 und 50000 corresponds to duty cycle between 1280 and 64000
	uint16_t new_max_duty_cycle = BETWEEN(1280, 64000000/drv8701.pwm_frequency, 64000);

	if(new_max_duty_cycle != drv8701.max_duty_cycle) {
		drv8701.max_duty_cycle = new_max_duty_cycle;
		ccu4_pwm_set_period(DRV8701_IN1_SLICE, drv8701.max_duty_cycle - 1);
		ccu4_pwm_set_period(DRV8701_IN2_SLICE, drv8701.max_duty_cycle - 1);
	}
}

void drv8701_tick_update_velocity(const uint32_t t) {
	static uint32_t last_t = 0;

	// We increase the veolocty once per ms, if more then
	// one ms has past we increase with an apropriate factor.
	const uint32_t factor = (uint32_t)(t - last_t);
	if(factor == 0) {
		return;
	}

	last_t = t;

	int16_t current_velocity = drv8701.velocity_current_high_res/1000;
	if(drv8701.velocity > current_velocity) {
		if(current_velocity > 0) {
			if(drv8701.acceleration == 0) {
				drv8701.velocity_current_high_res = drv8701.velocity*1000;
			} else {
				drv8701.velocity_current_high_res += MAX(1, drv8701.acceleration)*factor;
			}
		} else {
			if(drv8701.deceleration == 0) {
				drv8701.velocity_current_high_res = drv8701.velocity*1000;
			} else {
				drv8701.velocity_current_high_res += MAX(1, drv8701.deceleration)*factor;
			}
		}
		if(drv8701.velocity*1000 < drv8701.velocity_current_high_res) {
			drv8701.velocity_current_high_res = drv8701.velocity*1000;
		}
	} else if(drv8701.velocity < current_velocity) {
		if(current_velocity > 0) {
			if(drv8701.deceleration == 0) {
				drv8701.velocity_current_high_res = drv8701.velocity*1000;
			} else {
				drv8701.velocity_current_high_res -= MAX(1, drv8701.deceleration)*factor;
			}
		} else {
			if(drv8701.acceleration == 0) {
				drv8701.velocity_current_high_res = drv8701.velocity*1000;
			} else {
				drv8701.velocity_current_high_res -= MAX(1, drv8701.acceleration)*factor;
			}
		}
		if(drv8701.velocity*1000 > drv8701.velocity_current_high_res) {
			drv8701.velocity_current_high_res = drv8701.velocity*1000;
		}
	} else {
		// If velocity is already reached we return here so we never send
		// the velocity reached callback more then once.
		return;
	}

	if(drv8701.velocity == drv8701.velocity_current_high_res/1000) {
		drv8701.velocity_reached = true;
	}
}

void drv8701_check_thermal_shudown(void) {
	// voltage.temperature is in °C*10 and rv8701.thermal_shutdown_temperature is in °C
	if(voltage.temperature > (drv8701.thermal_shutdown_temperature*10)) {
		if(drv8701.enabled) {
			drv8701.enabled          = false;
			drv8701.thermal_shutdown = true;
		}
	}
}

void drv8701_tick(void) {
	const uint32_t t = system_timer_get_ms();

	drv8701_check_thermal_shudown();

	if(drv8701.enabled) {
		XMC_GPIO_SetOutputHigh(DRV8701_NSLEEP_PIN);
	} else {
		XMC_GPIO_SetOutputLow(DRV8701_NSLEEP_PIN);
	}

	drv8701_tick_update_frequency();
	drv8701_tick_update_velocity(t);
	int32_t new_velocity = drv8701.velocity_current_high_res/1000;

	if(drv8701.full_brake) {
		ccu4_pwm_set_duty_cycle(DRV8701_IN1_SLICE, drv8701.max_duty_cycle);
		ccu4_pwm_set_duty_cycle(DRV8701_IN2_SLICE, drv8701.max_duty_cycle);
		drv8701.velocity = 0;
		drv8701.velocity_current_high_res = 0;
	} else {
		if(drv8701.drive_mode == PERFORMANCE_DC_DRIVE_MODE_DRIVE_BRAKE) { // drive/brake
			if(new_velocity == 0) {
				ccu4_pwm_set_duty_cycle(DRV8701_IN1_SLICE, drv8701.max_duty_cycle);
				ccu4_pwm_set_duty_cycle(DRV8701_IN2_SLICE, drv8701.max_duty_cycle);
			} else if(new_velocity < 0) {
				ccu4_pwm_set_duty_cycle(DRV8701_IN1_SLICE, drv8701.max_duty_cycle);
				ccu4_pwm_set_duty_cycle(DRV8701_IN2_SLICE, drv8701.max_duty_cycle - SCALE(ABS(new_velocity), 0, INT16_MAX, 0, drv8701.max_duty_cycle));
			} else {
				ccu4_pwm_set_duty_cycle(DRV8701_IN2_SLICE, drv8701.max_duty_cycle);
				ccu4_pwm_set_duty_cycle(DRV8701_IN1_SLICE, drv8701.max_duty_cycle - SCALE(ABS(new_velocity), 0, INT16_MAX, 0, drv8701.max_duty_cycle));
			}
		} else { // drive/coast
			if(new_velocity == 0) {
				ccu4_pwm_set_duty_cycle(DRV8701_IN1_SLICE, 0);
				ccu4_pwm_set_duty_cycle(DRV8701_IN2_SLICE, 0);
			} else if(new_velocity < 0) {
				ccu4_pwm_set_duty_cycle(DRV8701_IN1_SLICE, 0);
				ccu4_pwm_set_duty_cycle(DRV8701_IN2_SLICE, SCALE(ABS(new_velocity), 0, INT16_MAX, 0, drv8701.max_duty_cycle));
			} else {
				ccu4_pwm_set_duty_cycle(DRV8701_IN2_SLICE, 0);
				ccu4_pwm_set_duty_cycle(DRV8701_IN1_SLICE, SCALE(ABS(new_velocity), 0, INT16_MAX, 0, drv8701.max_duty_cycle));
			}
		}
	}
	
	drv8701_handle_error_led(t);
	drv8701_handle_cw_led(t);
	drv8701_handle_ccw_led(t);
}
