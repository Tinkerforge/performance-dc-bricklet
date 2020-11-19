/* performance-dc-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * drv8701.h: Driver for DRV8701
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

#ifndef DRV8701_H
#define DRV8701_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib2/utility/led_flicker.h"

typedef struct {
	int16_t velocity;
	int16_t velocity_current;

	int32_t velocity_current_high_res;

	uint16_t acceleration;
	uint16_t deceleration;
	uint16_t pwm_frequency;

	bool full_brake;
	bool enabled;

	uint8_t drive_mode;

	LEDFlickerState error_led_flicker_state;
	LEDFlickerState cw_led_flicker_state;
	LEDFlickerState ccw_led_flicker_state;

	uint16_t max_duty_cycle;

	uint8_t thermal_shutdown_temperature;

	bool cb_emergency_shutdown_enabled;
	bool cb_velocity_reached_enabled;
	uint32_t cb_curent_velocity_period;
	bool cb_current_velocity_value_has_to_change;

	bool velocity_reached;
	bool thermal_shutdown;
} DRV8701;

extern DRV8701 drv8701;

void drv8701_init(void);
void drv8701_tick(void);

#endif