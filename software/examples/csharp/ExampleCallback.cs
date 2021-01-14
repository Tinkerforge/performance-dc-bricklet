using System;
using System.Threading;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Performance DC Bricklet

	// Use velocity reached callback to swing back and forth
	// between full speed forward and full speed backward
	static void VelocityReachedCB(BrickletPerformanceDC sender, short velocity)
	{
		if(velocity == 32767)
		{
			Console.WriteLine("Velocity: Full speed forward, now turning backward");
			sender.SetVelocity(-32767);
		}
		else if(velocity == -32767)
		{
			Console.WriteLine("Velocity: Full speed backward, now turning forward");
			sender.SetVelocity(32767);
		}
		else
		{
			// Can only happen if another program sets velocity
			Console.WriteLine("Error");
		}
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletPerformanceDC pdc = new BrickletPerformanceDC(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register velocity reached callback to function VelocityReachedCB
		pdc.VelocityReachedCallback += VelocityReachedCB;

		// Enable velocity reached callback
		pdc.SetVelocityReachedCallbackConfiguration(true);

		// The acceleration has to be smaller or equal to the maximum
		// acceleration of the DC motor, otherwise the velocity reached
		// callback will be called too early
		pdc.SetMotion(4096, 4096); // Slow acceleration (12.5 %/s)
		pdc.SetVelocity(32767); // Full speed forward (100 %)

		// Enable motor power
		pdc.SetEnabled(true);

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
