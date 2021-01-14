import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletPerformanceDC;

public class ExampleConfiguration {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your Performance DC Bricklet
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletPerformanceDC pdc = new BrickletPerformanceDC(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		pdc.setDriveMode(BrickletPerformanceDC.DRIVE_MODE_DRIVE_COAST);
		pdc.setPWMFrequency(10000); // Use PWM frequency of 10 kHz
		pdc.setMotion(4096, 4096); // Slow ac-/deceleration (12.5 %/s)
		pdc.setVelocity(32767); // Full speed forward (100 %)
		pdc.setEnabled(true); // Enable motor power

		System.out.println("Press key to exit"); System.in.read();

		// Stop motor before disabling motor power
		pdc.setMotion(4096, 16384); // Fast decceleration (50 %/s) for stopping
		pdc.setVelocity(0); // Request motor stop
		Thread.sleep(2000); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
		pdc.setEnabled(false); // Disable motor power

		ipcon.disconnect();
	}
}
