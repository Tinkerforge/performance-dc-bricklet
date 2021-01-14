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

	pdc.SetDriveMode(performance_dc_bricklet.DriveModeDriveCoast)
	pdc.SetPWMFrequency(10000) // Use PWM frequency of 10 kHz
	pdc.SetMotion(4096, 4096)  // Slow ac-/deceleration (12.5 %/s)
	pdc.SetVelocity(32767)     // Full speed forward (100 %)
	pdc.SetEnabled(true)       // Enable motor power

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

	// Stop motor before disabling motor power
	pdc.SetMotion(4096, 16384)          // Fast decceleration (50 %/s) for stopping
	pdc.SetVelocity(0)                  // Request motor stop
	time.Sleep(2000 * time.Millisecond) // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
	pdc.SetEnabled(false)               // Disable motor power
}
