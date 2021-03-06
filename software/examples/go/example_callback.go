package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
	"github.com/Tinkerforge/go-api-bindings/performance_dc_bricklet"
	"time"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Performance DC Bricklet.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	pdc, _ := performance_dc_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	pdc.RegisterVelocityReachedCallback(func(velocity int16) {
		if velocity == 32767 {
			fmt.Println("Velocity: Full speed forward, now turning backward")
			pdc.SetVelocity(-32767)
		} else if velocity == -32767 {
			fmt.Println("Velocity: Full speed backward, now turning forward")
			pdc.SetVelocity(32767)
		} else {
			//can only happen if another program sets velocity
			fmt.Println("Error")
		}
	})

	// Enable velocity reached callback
	pdc.SetVelocityReachedCallbackConfiguration(true)

	// The acceleration has to be smaller or equal to the maximum
	// acceleration of the DC motor, otherwise the velocity reached
	// callback will be called too early
	pdc.SetMotion(4096, 4096) // Slow acceleration (12.5 %/s)
	pdc.SetVelocity(32767)    // Full speed forward (100 %)

	// Enable motor power
	pdc.SetEnabled(true)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

	// Stop motor before disabling motor power
	pdc.SetMotion(4096, 16384)          // Fast decceleration (50 %/s) for stopping
	pdc.SetVelocity(0)                  // Request motor stop
	time.Sleep(2000 * time.Millisecond) // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
	pdc.SetEnabled(false)               // Disable motor power
}
