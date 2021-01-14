import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletPerformanceDC;
import com.tinkerforge.TinkerforgeException;

public class ExampleCallback {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your Performance DC Bricklet
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		// Note: Declare pdc as final, so the listener can access it
		final BrickletPerformanceDC pdc = new BrickletPerformanceDC(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Use velocity reached callback to swing back and forth
		// between full speed forward and full speed backward
		pdc.addVelocityReachedListener(new BrickletPerformanceDC.VelocityReachedListener() {
			public void velocityReached(int velocity) {
				if(velocity == 32767) {
					System.out.println("Velocity: Full speed forward, now turning backward");
					try {
						pdc.setVelocity(-32767);
					} catch(TinkerforgeException e) {
					}
				} else if(velocity == -32767) {
					System.out.println("Velocity: Full speed backward, now turning forward");
					try {
						pdc.setVelocity(32767);
					} catch(TinkerforgeException e) {
					}
				} else {
					System.out.println("Error"); // Can only happen if another program sets velocity
				}
			}
		});

		// Enable velocity reached callback
		pdc.setVelocityReachedCallbackConfiguration(true);

		// The acceleration has to be smaller or equal to the maximum
		// acceleration of the DC motor, otherwise the velocity reached
		// callback will be called too early
		pdc.setMotion(4096, 4096); // Slow acceleration (12.5 %/s)
		pdc.setVelocity(32767); // Full speed forward (100 %)

		// Enable motor power
		pdc.setEnabled(true);

		System.out.println("Press key to exit"); System.in.read();

		// Stop motor before disabling motor power
		pdc.setMotion(4096, 16384); // Fast decceleration (50 %/s) for stopping
		pdc.setVelocity(0); // Request motor stop
		Thread.sleep(2000); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
		pdc.setEnabled(false); // Disable motor power

		ipcon.disconnect();
	}
}
