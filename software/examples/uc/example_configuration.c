// This example is not self-contained.
// It requires usage of the example driver specific to your platform.
// See the HAL documentation.

#include "src/bindings/hal_common.h"
#include "src/bindings/bricklet_performance_dc.h"

void check(int rc, const char *msg);
void example_setup(TF_HAL *hal);
void example_loop(TF_HAL *hal);

static TF_PerformanceDC pdc;

void example_setup(TF_HAL *hal) {
	// Create device object
	check(tf_performance_dc_create(&pdc, NULL, hal), "create device object");

	check(tf_performance_dc_set_drive_mode(&pdc,
	                                       TF_PERFORMANCE_DC_DRIVE_MODE_DRIVE_COAST), "call set_drive_mode");
	check(tf_performance_dc_set_pwm_frequency(&pdc,
	                                          10000), "call set_pwm_frequency"); // Use PWM frequency of 10 kHz
	check(tf_performance_dc_set_motion(&pdc, 4096,
	                                   4096), "call set_motion"); // Slow ac-/deceleration (12.5 %/s)
	check(tf_performance_dc_set_velocity(&pdc,
	                                     32767), "call set_velocity"); // Full speed forward (100 %)
	check(tf_performance_dc_set_enabled(&pdc,
	                                    true), "call set_enabled"); // Enable motor power
}

void example_loop(TF_HAL *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
