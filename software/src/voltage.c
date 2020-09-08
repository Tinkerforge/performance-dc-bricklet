/* dc-v2-bricklet
 * Copyright (C) 2020 Olaf Lüke <olaf@tinkerforge.com>
 *
 * voltage.c: Driver for DC Bricklet 2.0 voltage measurements
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

#include "voltage.h"
#include "configs/config_voltage.h"

#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/logging/logging.h"

#include "xmc_vadc.h"

Voltage voltage;

void voltage_init_adc(void) {
	// This structure contains the Global related Configuration.
	const XMC_VADC_GLOBAL_CONFIG_t adc_global_config = {
		.boundary0 = (uint32_t) 0, // Lower boundary value for Normal comparison mode
		.boundary1 = (uint32_t) 0, // Upper boundary value for Normal comparison mode

		.class0 = {
			.sample_time_std_conv     = 31,                      // The Sample time is (2*tadci)
			.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT, // 12bit conversion Selected

		},
		.class1 = {
			.sample_time_std_conv     = 31,                      // The Sample time is (2*tadci)
			.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT, // 12bit conversion Selected

		},

		.data_reduction_control         = 0b11, // Accumulate 4 result values
		.wait_for_read_mode             = 0, // GLOBRES Register will not be overwritten until the previous value is read
		.event_gen_enable               = 0, // Result Event from GLOBRES is disabled
		.disable_sleep_mode_control     = 0  // Sleep mode is enabled
	};


	// Global iclass0 configuration
	const XMC_VADC_GLOBAL_CLASS_t adc_global_iclass_config = {
		.conversion_mode_standard = XMC_VADC_CONVMODE_12BIT,
		.sample_time_std_conv	  = 31,
	};

	// Global Result Register configuration structure
	XMC_VADC_RESULT_CONFIG_t adc_global_result_config = {
		.data_reduction_control = 0b11,  // Accumulate 4 result values
		.post_processing_mode   = XMC_VADC_DMM_REDUCTION_MODE,
		.wait_for_read_mode  	= 1, // Enabled
		.part_of_fifo       	= 0, // No FIFO
		.event_gen_enable   	= 0  // Disable Result event
	};

	// LLD Background Scan Init Structure
	const XMC_VADC_BACKGROUND_CONFIG_t adc_background_config = {
		.conv_start_mode   = XMC_VADC_STARTMODE_CIR,       // Conversion start mode selected as cancel inject repeat
		.req_src_priority  = XMC_VADC_GROUP_RS_PRIORITY_1, // Priority of the Background request source in the VADC module
		.trigger_signal    = XMC_VADC_REQ_TR_A,            // If Trigger needed then this denotes the Trigger signal
		.trigger_edge      = XMC_VADC_TRIGGER_EDGE_NONE,   // If Trigger needed then this denotes Trigger edge selected
		.gate_signal       = XMC_VADC_REQ_GT_A,			   // If Gating needed then this denotes the Gating signal
		.timer_mode        = 0,							   // Timer Mode Disabled
		.external_trigger  = 0,                            // Trigger is Disabled
		.req_src_interrupt = 0,                            // Background Request source interrupt Disabled
		.enable_auto_scan  = 1,
		.load_mode         = XMC_VADC_SCAN_LOAD_OVERWRITE
	};

	const XMC_VADC_GROUP_CONFIG_t group_init_handle0 = {
		.emux_config = {
			.stce_usage                  = 0, 					           // Use STCE when the setting changes
			.emux_mode                   = XMC_VADC_GROUP_EMUXMODE_SWCTRL, // Mode for Emux conversion
			.emux_coding                 = XMC_VADC_GROUP_EMUXCODE_BINARY, // Channel progression - binary format
			.starting_external_channel   = 0,                              // Channel starts at 0 for EMUX
			.connected_channel           = 0                               // Channel connected to EMUX
		},
		.class0 = {
			.sample_time_std_conv        = 31,                             // The Sample time is (2*tadci)
			.conversion_mode_standard    = XMC_VADC_CONVMODE_12BIT,        // 12bit conversion Selected
			.sampling_phase_emux_channel = 0,                              // The Sample time is (2*tadci)
			.conversion_mode_emux        = XMC_VADC_CONVMODE_12BIT         // 12bit conversion Selected
		},
		.class1 = {
			.sample_time_std_conv        = 31,                             // The Sample time is (2*tadci)
			.conversion_mode_standard    = XMC_VADC_CONVMODE_12BIT,        // 12bit conversion Selected
			.sampling_phase_emux_channel = 0,                              // The Sample time is (2*tadci)
			.conversion_mode_emux        = XMC_VADC_CONVMODE_12BIT         // 12bit conversion Selected
		},

		.boundary0                       = 0,                              // Lower boundary value for Normal comparison mode
		.boundary1	                     = 0,                              // Upper boundary value for Normal comparison mode
		.arbitration_round_length        = 0,                              // 4 arbitration slots per round selected (tarb = 4*tadcd) */
		.arbiter_mode                    = XMC_VADC_GROUP_ARBMODE_ALWAYS,  // Determines when the arbiter should run.
	};


	XMC_VADC_CHANNEL_CONFIG_t  channel_so_config = {
		.input_class                =  XMC_VADC_CHANNEL_CONV_GLOBAL_CLASS0,    // Global ICLASS 0 selected
		.lower_boundary_select 	    =  XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.upper_boundary_select 	    =  XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.event_gen_criteria         =  XMC_VADC_CHANNEL_EVGEN_NEVER,           // Channel Event disabled
		.sync_conversion  		    =  0,                                      // Sync feature disabled
		.alternate_reference        =  XMC_VADC_CHANNEL_REF_INTREF,            // Internal reference selected
		.result_reg_number          =  VOLTAGE_SO_RESULT_REG,         // GxRES[10] selected
		.use_global_result          =  0, 				                       // Use Group result register
		.result_alignment           =  XMC_VADC_RESULT_ALIGN_RIGHT,            // Result alignment - Right Aligned
		.broken_wire_detect_channel =  XMC_VADC_CHANNEL_BWDCH_VAGND,           // No Broken wire mode select
		.broken_wire_detect		    =  0,    		                           // No Broken wire detection
		.bfl                        =  0,                                      // No Boundary flag
		.channel_priority           =  0,                   		           // Lowest Priority 0 selected
		.alias_channel              =  VOLTAGE_SO_ALIAS               // Channel is Aliased
	};

	XMC_VADC_CHANNEL_CONFIG_t  channel_vin_config = {
		.input_class                =  XMC_VADC_CHANNEL_CONV_GLOBAL_CLASS0,    // Global ICLASS 0 selected
		.lower_boundary_select 	    =  XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.upper_boundary_select 	    =  XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.event_gen_criteria         =  XMC_VADC_CHANNEL_EVGEN_NEVER,           // Channel Event disabled
		.sync_conversion  		    =  0,                                      // Sync feature disabled
		.alternate_reference        =  XMC_VADC_CHANNEL_REF_INTREF,            // Internal reference selected
		.result_reg_number          =  VOLTAGE_VIN_RESULT_REG,    // GxRES[10] selected
		.use_global_result          =  0, 				                       // Use Group result register
		.result_alignment           =  XMC_VADC_RESULT_ALIGN_RIGHT,            // Result alignment - Right Aligned
		.broken_wire_detect_channel =  XMC_VADC_CHANNEL_BWDCH_VAGND,           // No Broken wire mode select
		.broken_wire_detect		    =  0,    		                           // No Broken wire detection
		.bfl                        =  0,                                      // No Boundary flag
		.channel_priority           =  0,                   		           // Lowest Priority 0 selected
		.alias_channel              =  VOLTAGE_VIN_ALIAS          // Channel is Aliased
	};

	XMC_VADC_CHANNEL_CONFIG_t  channel_temp_config = {
		.input_class                =  XMC_VADC_CHANNEL_CONV_GLOBAL_CLASS0,    // Global ICLASS 0 selected
		.lower_boundary_select 	    =  XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.upper_boundary_select 	    =  XMC_VADC_CHANNEL_BOUNDARY_GROUP_BOUND0,
		.event_gen_criteria         =  XMC_VADC_CHANNEL_EVGEN_NEVER,           // Channel Event disabled
		.sync_conversion  		    =  0,                                      // Sync feature disabled
		.alternate_reference        =  XMC_VADC_CHANNEL_REF_INTREF,            // Internal reference selected
		.result_reg_number          =  VOLTAGE_TEMP_RESULT_REG,    // GxRES[10] selected
		.use_global_result          =  0, 				                       // Use Group result register
		.result_alignment           =  XMC_VADC_RESULT_ALIGN_RIGHT,            // Result alignment - Right Aligned
		.broken_wire_detect_channel =  XMC_VADC_CHANNEL_BWDCH_VAGND,           // No Broken wire mode select
		.broken_wire_detect		    =  0,    		                           // No Broken wire detection
		.bfl                        =  0,                                      // No Boundary flag
		.channel_priority           =  0,                   		           // Lowest Priority 0 selected
		.alias_channel              =  VOLTAGE_TEMP_ALIAS          // Channel is Aliased
	};

	XMC_VADC_RESULT_CONFIG_t channel_result_config =
	{
		.data_reduction_control = 0b11,                         // Accumulate 4 result values
		.post_processing_mode   = XMC_VADC_DMM_REDUCTION_MODE,  // Use reduction mode
		.wait_for_read_mode  	= 1,                            // Enabled
		.part_of_fifo       	= 0 ,                           // No FIFO
		.event_gen_enable   	= 0                             // Disable Result event
	};


	XMC_VADC_GLOBAL_Init(VADC, &adc_global_config);

	XMC_VADC_GROUP_Init(VADC_G0, &group_init_handle0);
	XMC_VADC_GROUP_SetPowerMode(VADC_G0, XMC_VADC_GROUP_POWERMODE_NORMAL);

	XMC_VADC_GLOBAL_SHS_EnableAcceleratedMode(SHS0, XMC_VADC_GROUP_INDEX_0);
	XMC_VADC_GLOBAL_SHS_SetAnalogReference(SHS0, XMC_VADC_GLOBAL_SHS_AREF_EXTERNAL_VDD_UPPER_RANGE);

	XMC_VADC_GLOBAL_StartupCalibration(VADC);

	// Initialize the Global Conversion class 0
	XMC_VADC_GLOBAL_InputClassInit(VADC, adc_global_iclass_config, XMC_VADC_GROUP_CONV_STD, 0);

	// Initialize the Background Scan hardware
	XMC_VADC_GLOBAL_BackgroundInit(VADC, &adc_background_config);

	// Initialize the global result register
	XMC_VADC_GLOBAL_ResultInit(VADC, &adc_global_result_config);

	// Initialize for configured channels
	XMC_VADC_GROUP_ChannelInit(VADC_G0, VOLTAGE_SO_CHANNEL_NUM,   &channel_so_config);
	XMC_VADC_GROUP_ChannelInit(VADC_G0, VOLTAGE_VIN_CHANNEL_NUM,  &channel_vin_config);
	XMC_VADC_GROUP_ChannelInit(VADC_G0, VOLTAGE_TEMP_CHANNEL_NUM, &channel_temp_config);

	// Initialize for configured result registers
	XMC_VADC_GROUP_ResultInit(VADC_G0, channel_so_config.result_reg_number,   &channel_result_config);
	XMC_VADC_GROUP_ResultInit(VADC_G0, channel_vin_config.result_reg_number,  &channel_result_config);
	XMC_VADC_GROUP_ResultInit(VADC_G0, channel_temp_config.result_reg_number, &channel_result_config);

	XMC_VADC_GLOBAL_BackgroundAddChannelToSequence(VADC, 0, VOLTAGE_SO_CHANNEL_NUM);
	XMC_VADC_GLOBAL_BackgroundAddChannelToSequence(VADC, 0, VOLTAGE_VIN_CHANNEL_NUM);
	XMC_VADC_GLOBAL_BackgroundAddChannelToSequence(VADC, 0, VOLTAGE_TEMP_CHANNEL_NUM);

	XMC_VADC_GLOBAL_BackgroundTriggerConversion(VADC);
}

void voltage_init(void) {
	const XMC_GPIO_CONFIG_t input_default_config = {
		.mode             = XMC_GPIO_MODE_INPUT_TRISTATE,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
	};

	XMC_GPIO_Init(VOLTAGE_VIN_PIN,  &input_default_config);
	XMC_GPIO_Init(VOLTAGE_SO_PIN,   &input_default_config);
	XMC_GPIO_Init(VOLTAGE_TEMP_PIN, &input_default_config);

	voltage_init_adc();
}

void voltage_tick(void) {
	const uint32_t result_vin  = XMC_VADC_GROUP_GetDetailedResult(VADC_G0, VOLTAGE_VIN_RESULT_REG);
	const uint32_t result_so   = XMC_VADC_GROUP_GetDetailedResult(VADC_G0, VOLTAGE_SO_RESULT_REG);
	const uint32_t result_temp = XMC_VADC_GROUP_GetDetailedResult(VADC_G0, VOLTAGE_TEMP_RESULT_REG);


	if((result_vin & (1 << 31))) {
		voltage.adc_sum_vin += (result_vin & 0xFFFF);
		voltage.adc_count_vin++;
	}

	if((result_so & (1 << 31))) {
		voltage.adc_sum_so += (result_so & 0xFFFF);
		voltage.adc_count_so++;
	}

	if((result_temp & (1 << 31))) {
		voltage.adc_sum_temp += (result_temp & 0xFFFF);
		voltage.adc_count_temp++;
	}

	if(system_timer_is_time_elapsed_ms(voltage.adc_last_time, 100)) {
		voltage.adc_last_time = system_timer_get_ms();

		// VIN voltage divider: 100k/10k => 3300*11/(4095*4) => 605/273
		if(voltage.adc_count_vin != 0) {
			voltage.voltage = (voltage.adc_sum_vin*605)/(voltage.adc_count_vin*273);
		}

		// SO Voltage:
		// I       = (SO - V_OFF) / (A_V * R_SENSE)
		// V_OFF   = ?
		// A_V     = 20 V/V
		// R_SENSE = 0.01 Ohm
		// => I    = (SO - V_OFF) / (20 * 0.01) = (SO - V_OFF) * 5

		// SO voltage divider: 10k/7.5k => 5*3300*100/(4095*4*175) => 1100/1911 ~= 110/191
		if(voltage.adc_count_so != 0) {
			voltage.current = (voltage.adc_sum_so*110)/(voltage.adc_count_so*191);
		}

		// Temperature according to tmp235 datasheet 7.3, but we calculate on ADC values insteadof mV
		// T_A    = (V_OUT – V_OFFS ) / T_C + T_INFL
		// V_OUT  = ADC
		// V_OFF  = 500/(3300/(4095*4)) = 2481.8181
		// T_C    = 10/(3300/(4095*4))  = 49.6363
		// T_INFL = 0
		if(voltage.adc_count_temp != 0) {
			voltage.temperature = (voltage.adc_sum_temp/((int32_t)voltage.adc_count_temp) - 2482)*100/496;
		}

		voltage.adc_count_vin  = 0;
		voltage.adc_count_so   = 0;
		voltage.adc_count_temp = 0;
		voltage.adc_sum_vin    = 0;
		voltage.adc_sum_so     = 0;
		voltage.adc_sum_temp   = 0;

		logd("Voltage: %dmV, Current: %dmA, Temperature: %d\n\r", voltage.voltage, voltage.current, voltage.temperature);
	}
}