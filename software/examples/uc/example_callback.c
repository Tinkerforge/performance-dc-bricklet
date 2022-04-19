// This example is not self-contained.
// It requres usage of the example driver specific to your platform.
// See the HAL documentation.

#include "bindings/hal_common.h"
#include "bindings/bricklet_performance_dc.h"

// FIXME: This example is incomplete

#define UID "XYZ" // Change XYZ to the UID of your Performance DC Bricklet

void check(int rc, const char* msg);

void example_setup(TF_HAL *hal);
void example_loop(TF_HAL *hal);


// Use velocity reached callback to swing back and forth
// between full speed forward and full speed backward
static void velocity_reached_handler(TF_PerformanceDC *device, int16_t velocity,
                                     void *user_data) {
	(void)device; (void)user_data; // avoid unused parameter warning

	tf_hal_printf("Velocity: %I16d\n", velocity);
}

static TF_PerformanceDC pdc;

void example_setup(TF_HAL *hal) {
	// Create device object
	check(tf_performance_dc_create(&pdc, UID, hal), "create device object");

	// Register velocity reached callback to function velocity_reached_handler
	tf_performance_dc_register_velocity_reached_callback(&pdc,
	                                                     velocity_reached_handler,
	                                                     NULL);

	// Enable velocity reached callback
	check(tf_performance_dc_set_velocity_reached_callback_configuration(&pdc,
	                                                                    true), "call set_velocity_reached_callback_configuration");

	// The acceleration has to be smaller or equal to the maximum
	// acceleration of the DC motor, otherwise the velocity reached
	// callback will be called too early
	check(tf_performance_dc_set_motion(&pdc, 4096,
	                                   4096), "call set_motion"); // Slow acceleration (12.5 %/s)
	check(tf_performance_dc_set_velocity(&pdc,
	                                     32767), "call set_velocity"); // Full speed forward (100 %)

	// Enable motor power
	check(tf_performance_dc_set_enabled(&pdc, true), "call set_enabled");
}

void example_loop(TF_HAL *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
