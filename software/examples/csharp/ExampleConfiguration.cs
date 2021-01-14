using System;
using System.Threading;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Performance DC Bricklet

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletPerformanceDC pdc = new BrickletPerformanceDC(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		pdc.SetDriveMode(BrickletPerformanceDC.DRIVE_MODE_DRIVE_COAST);
		pdc.SetPWMFrequency(10000); // Use PWM frequency of 10 kHz
		pdc.SetMotion(4096, 4096); // Slow ac-/deceleration (12.5 %/s)
		pdc.SetVelocity(32767); // Full speed forward (100 %)
		pdc.SetEnabled(true); // Enable motor power

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();

		// Stop motor before disabling motor power
		pdc.SetMotion(4096, 16384); // Fast decceleration (50 %/s) for stopping
		pdc.SetVelocity(0); // Request motor stop
		Thread.Sleep(2000); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
		pdc.SetEnabled(false); // Disable motor power

		ipcon.Disconnect();
	}
}
