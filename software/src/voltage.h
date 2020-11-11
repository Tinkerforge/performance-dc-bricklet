/* performance-dc-bricklet
 * Copyright (C) 2020 Olaf Lüke <olaf@tinkerforge.com>
 *
 * voltage.h: Driver for Performance DC Bricklet voltage measurements
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

#ifndef VOLTAGE_H
#define VOLTAGE_H

#include <stdint.h>

typedef struct {
    uint16_t voltage;
    uint16_t current;
    int16_t  temperature;

    uint64_t adc_sum_so;
    uint64_t adc_sum_vin;
    uint64_t adc_sum_temp;

    uint32_t adc_count_so;
    uint32_t adc_count_vin;
    uint32_t adc_count_temp;

    uint32_t adc_last_time;
} Voltage;

extern Voltage voltage;

void voltage_init(void);
void voltage_tick(void);

#endif