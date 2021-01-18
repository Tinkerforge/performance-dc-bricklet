/* performance-dc-bricklet
 * Copyright (C) 2020 Olaf Lüke <olaf@tinkerforge.com>
 *
 * gpio.c: Driver for Performance DC Bricklet GPIO
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

#include "gpio.h"
#include "configs/config_gpio.h"

#include "communication.h"
#include "drv8701.h"

#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/logging/logging.h"

#include "xmc_gpio.h"
#include "xmc_eru.h"

#define gpio_0_handler IRQ_Hdlr_4
#define gpio_1_handler IRQ_Hdlr_6

typedef struct {
	XMC_GPIO_PORT_t *const port;
	const uint8_t pin;
	uint8_t irq_n;
} GPIOPins;

static const GPIOPins gpio_pins[GPIO_CHANNEL_NUM] = {
	{GPIO_0_PIN, GPIO_0_IRQ_N},
	{GPIO_1_PIN, GPIO_1_IRQ_N}
};

static const GPIOPins gpio_led_pins[GPIO_CHANNEL_NUM] = {
	{GPIO_0_LED_PIN, 0},
	{GPIO_1_LED_PIN, 0}
};

GPIO gpio;

static inline void __attribute__((optimize("-O3"))) __attribute__ ((section (".ram_code"))) handle_new_gpio_value(const uint8_t channel) {
	// Check if value changed
	const bool value = XMC_GPIO_GetInput(gpio_pins[channel].port, gpio_pins[channel].pin);
	if(gpio.last_interrupt_value[channel] == value) {
		return;
	}

	// Save value
	gpio.last_interrupt_value[channel] = value;

	// Turn interrupt off if debounce is enabled
	if(gpio.debounce[channel] != 0) {
		gpio.last_interrupt_time[channel]  = system_timer_get_ms();
		NVIC_DisableIRQ(gpio_pins[channel].irq_n);
		NVIC_ClearPendingIRQ(gpio_pins[channel].irq_n);
	}

	// TODO: handle callback here

	// Check if action is necessary
	if(value && (gpio.action[channel] & PERFORMANCE_DC_GPIO_ACTION_FULL_BRAKE_RISING_EDGE)) {
		gpio.stop_emergency  = true;
		drv8701.full_brake   = true;
	} else if(value && (gpio.action[channel] & PERFORMANCE_DC_GPIO_ACTION_NORMAL_STOP_RISING_EDGE)) {
		gpio.stop_normal     = true;
		drv8701.deceleration = gpio.stop_deceleration[channel];
		drv8701.velocity     = 0;
	} else if(!value && (gpio.action[channel] & PERFORMANCE_DC_GPIO_ACTION_FULL_BRAKE_FALLING_EDGE)) {
		gpio.stop_emergency  = true;
		drv8701.full_brake   = true;
	} else if(!value && (gpio.action[channel] & PERFORMANCE_DC_GPIO_ACTION_NORMAL_STOP_FALLING_EDGE)) {
		gpio.stop_normal     = true;
		drv8701.deceleration = gpio.stop_deceleration[channel];
		drv8701.velocity     = 0;
	}

	// Set LED
	if(gpio.gpio_led_flicker_state[channel].config == PERFORMANCE_DC_GPIO_LED_CONFIG_SHOW_GPIO_ACTIVE_HIGH) {
		if(value) {
			XMC_GPIO_SetOutputLow(gpio_led_pins[channel].port, gpio_led_pins[channel].pin);
		} else {
			XMC_GPIO_SetOutputHigh(gpio_led_pins[channel].port, gpio_led_pins[channel].pin);
		}
	} else if(gpio.gpio_led_flicker_state[channel].config == PERFORMANCE_DC_GPIO_LED_CONFIG_SHOW_GPIO_ACTIVE_LOW) {
		if(value) {
			XMC_GPIO_SetOutputHigh(gpio_led_pins[channel].port, gpio_led_pins[channel].pin);
		} else {
			XMC_GPIO_SetOutputLow(gpio_led_pins[channel].port, gpio_led_pins[channel].pin);
		}
	}
}

void __attribute__((optimize("-O3"))) __attribute__ ((section (".ram_code"))) gpio_0_handler(void) {
	handle_new_gpio_value(0);
}

void __attribute__((optimize("-O3"))) __attribute__ ((section (".ram_code"))) gpio_1_handler(void) {
	handle_new_gpio_value(1);
}

void gpio_init(void) {
    memset(&gpio, 0, sizeof(GPIO));

	gpio.action[0]                        = PERFORMANCE_DC_GPIO_ACTION_NONE;
	gpio.action[1]                        = PERFORMANCE_DC_GPIO_ACTION_NONE;
	gpio.debounce[0]                      = 50; // 50ms default
	gpio.debounce[1]                      = 50; // 50ms default
	gpio.stop_deceleration[0]             = 0xFFFF;
	gpio.stop_deceleration[1]             = 0xFFFF;
	gpio.gpio_led_flicker_state[0].config = PERFORMANCE_DC_GPIO_LED_CONFIG_SHOW_GPIO_ACTIVE_LOW;
	gpio.gpio_led_flicker_state[1].config = PERFORMANCE_DC_GPIO_LED_CONFIG_SHOW_GPIO_ACTIVE_LOW;


	// Init GPIO IRQs
	const XMC_GPIO_CONFIG_t gpio_pin_config = {
		.mode             = XMC_GPIO_MODE_INPUT_TRISTATE,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_LARGE
	};

	const XMC_ERU_ETL_CONFIG_t sync_etl_0_config = {
		.input_a                = GPIO_0_INPUT_A,
		.input_b                = GPIO_0_INPUT_B,
		.enable_output_trigger  = 1,
		.edge_detection         = XMC_ERU_ETL_EDGE_DETECTION_BOTH,
		.output_trigger_channel = GPIO_0_TRG_CHANNEL,
		.source                 = GPIO_0_SOURCE
	};

	XMC_GPIO_Init(GPIO_0_PIN, &gpio_pin_config);
	XMC_ERU_ETL_Init(GPIO_0_ERU, GPIO_0_ETL_CHANNEL, &sync_etl_0_config);
	XMC_ERU_OGU_SetServiceRequestMode(GPIO_0_ERU, GPIO_0_OGU_CHANNEL, XMC_ERU_OGU_SERVICE_REQUEST_ON_TRIGGER);
	NVIC_SetPriority(GPIO_0_IRQ_N, GPIO_0_IRQ_PRIO);
	NVIC_ClearPendingIRQ(GPIO_0_IRQ_N);
	NVIC_EnableIRQ(GPIO_0_IRQ_N);


    const XMC_ERU_ETL_CONFIG_t sync_etl_1_config = {
		.input_a                = GPIO_1_INPUT_A,
		.input_b                = GPIO_1_INPUT_B,
		.enable_output_trigger  = 1,
		.edge_detection         = XMC_ERU_ETL_EDGE_DETECTION_BOTH,
		.output_trigger_channel = GPIO_1_TRG_CHANNEL,
		.source                 = GPIO_1_SOURCE
	};

	XMC_GPIO_Init(GPIO_1_PIN, &gpio_pin_config);
	XMC_ERU_ETL_Init(GPIO_1_ERU, GPIO_1_ETL_CHANNEL, &sync_etl_1_config);
	XMC_ERU_OGU_SetServiceRequestMode(GPIO_1_ERU, GPIO_1_OGU_CHANNEL, XMC_ERU_OGU_SERVICE_REQUEST_ON_TRIGGER);
	NVIC_SetPriority(GPIO_1_IRQ_N, GPIO_1_IRQ_PRIO);
	NVIC_ClearPendingIRQ(GPIO_1_IRQ_N);
	NVIC_EnableIRQ(GPIO_1_IRQ_N);


	// Init GPIO LEDs
	const XMC_GPIO_CONFIG_t led_pin_config = {
		.mode         = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
		.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW
	};

	for(uint8_t channel = 0; channel < GPIO_CHANNEL_NUM; channel++) {
		XMC_GPIO_Init(gpio_led_pins[channel].port, gpio_led_pins[channel].pin, &led_pin_config);

		const bool value = XMC_GPIO_GetInput(gpio_pins[channel].port, gpio_pins[channel].pin);
		gpio.last_interrupt_value[channel] = value;
		if(value) {
			XMC_GPIO_SetOutputHigh(gpio_led_pins[channel].port, gpio_led_pins[channel].pin);
		} else {
			XMC_GPIO_SetOutputLow(gpio_led_pins[channel].port, gpio_led_pins[channel].pin);
		}
	}
}

void gpio_tick(void) {
	// Enable interrupt again after debounce time
	for(uint8_t channel = 0; channel < GPIO_CHANNEL_NUM; channel++) {
		if(gpio.last_interrupt_time[channel] != 0) {
			if(system_timer_is_time_elapsed_ms(gpio.last_interrupt_time[channel], gpio.debounce[channel])) {
				gpio.last_interrupt_time[channel] = 0;
				NVIC_EnableIRQ(gpio_pins[channel].irq_n);
			}
		}

		if(gpio.gpio_led_flicker_state[channel].config == PERFORMANCE_DC_GPIO_LED_CONFIG_SHOW_HEARTBEAT) {
			led_flicker_tick(&drv8701.error_led_flicker_state, system_timer_get_ms(), gpio_led_pins[channel].port, gpio_led_pins[channel].pin);
		}
	}
}