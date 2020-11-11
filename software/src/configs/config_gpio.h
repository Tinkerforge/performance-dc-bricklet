/* performance-dc-bricklet
 * Copyright (C) 2020 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_gpio.h: Config for DRV8701 GPIO
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

#ifndef CONFIG_GPIO_H
#define CONFIG_GPIO_H

#include "xmc_gpio.h"
#include "xmc_eru.h"

#define GPIO_0_PIN          P2_1
#define GPIO_0_LED_PIN      P1_2
#define GPIO_0_ERU          XMC_ERU0
#define GPIO_0_ETL_CHANNEL  1
#define GPIO_0_OGU_CHANNEL  1
#define GPIO_0_INPUT_A      XMC_ERU_ETL_INPUT_A0
#define GPIO_0_INPUT_B      XMC_ERU_ETL_INPUT_B0
#define GPIO_0_TRG_CHANNEL  XMC_ERU_ETL_OUTPUT_TRIGGER_CHANNEL1
#define GPIO_0_SOURCE       XMC_ERU_ETL_SOURCE_B
#define GPIO_0_IRQ_N        4
#define GPIO_0_IRQ_PRIO     0
#define GPIO_0_IRQ_CTRL     0

#define GPIO_1_PIN          P2_9
#define GPIO_1_LED_PIN      P1_3
#define GPIO_1_ERU          XMC_ERU0
#define GPIO_1_ETL_CHANNEL  3
#define GPIO_1_OGU_CHANNEL  3
#define GPIO_1_INPUT_A      XMC_ERU_ETL_INPUT_A0
#define GPIO_1_INPUT_B      XMC_ERU_ETL_INPUT_B0
#define GPIO_1_TRG_CHANNEL  XMC_ERU_ETL_OUTPUT_TRIGGER_CHANNEL3
#define GPIO_1_SOURCE       XMC_ERU_ETL_SOURCE_B
#define GPIO_1_IRQ_N        6
#define GPIO_1_IRQ_PRIO     0
#define GPIO_1_IRQ_CTRL     0

#endif
