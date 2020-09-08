/* dc-v2-bricklet
 * Copyright (C) 2020 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_voltage.h: Config for DRV8701 voltage measurements
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

#ifndef CONFIG_VOLTAGE_H
#define CONFIG_VOLTAGE_H

#include "xmc_gpio.h"

#define VOLTAGE_SO_PIN            P2_11
#define VOLTAGE_SO_ALIAS          -1
#define VOLTAGE_SO_RESULT_REG     10
#define VOLTAGE_SO_CHANNEL_NUM    4

#define VOLTAGE_VIN_PIN           P2_7
#define VOLTAGE_VIN_ALIAS         -1
#define VOLTAGE_VIN_RESULT_REG    1
#define VOLTAGE_VIN_CHANNEL_NUM   1

#define VOLTAGE_TEMP_PIN          P2_10
#define VOLTAGE_TEMP_ALIAS        3
#define VOLTAGE_TEMP_RESULT_REG   0
#define VOLTAGE_TEMP_CHANNEL_NUM  0

#endif
