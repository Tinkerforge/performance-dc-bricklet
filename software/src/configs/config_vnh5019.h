/* performance-dc-bricklet
 * Copyright (C) 2019 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_vnh5019.h: Config for VNH5019 driver
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

#ifndef CONFIG_VNH5019_H
#define CONFIG_VNH5019_H

#define VNH5019_PWM_PIN         P1_0
#define VNH5019_ENABLE_A_PIN    P0_9
#define VNH5019_ENABLE_B_PIN    P0_7
#define VNH5019_IN_A_PIN        P0_12
#define VNH5019_IN_B_PIN        P0_6
#define VNH5019_CS_PIN          P2_11
#define VNH5019_CS_DISABLE_PIN  P0_8

#define VN5019_PWM_CCU4_SLICE   0

#endif
