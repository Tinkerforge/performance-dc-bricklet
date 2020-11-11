/* performance-dc-bricklet
 * Copyright (C) 2020 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_drv8701.h: Config for DRV8701 driver
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

#ifndef CONFIG_DRV8701_H
#define CONFIG_DRV8701_H

#include "xmc_gpio.h"

// We use DRV8701P witn IN1/IN2 instead of PH/EN!
#define DRV8701_IN1_PIN         P0_8
#define DRV8701_IN2_PIN         P0_7
#define DRV8701_NSLEEP_PIN      P0_6
#define DRV8701_SNSOUT_PIN      P2_6
#define DRV8701_NFAULT_PIN      P2_2

#define DRV8701_LED_CW_PIN      P1_0
#define DRV8701_LED_CCW_PIN     P1_1
#define DRV8701_LED_ERROR_PIN   P0_0

#define DRV8701_IN1_SLICE       2
#define DRV8701_IN2_SLICE       1

#endif
