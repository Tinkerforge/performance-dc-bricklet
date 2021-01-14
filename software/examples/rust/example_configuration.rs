use std::{error::Error, io, thread, time::Duration};
use tinkerforge::{ip_connection::IpConnection, performance_dc_bricklet::*};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Performance DC Bricklet.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let pdc = PerformanceDcBricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    pdc.set_drive_mode(PERFORMANCE_DC_BRICKLET_DRIVE_MODE_DRIVE_COAST).recv()?;
    pdc.set_pwm_frequency(10000).recv()?; // Use PWM frequency of 10 kHz
    pdc.set_motion(4096, 4096).recv()?; // Slow ac-/deceleration (12.5 %/s)
    pdc.set_velocity(32767).recv()?; // Full speed forward (100 %)
    pdc.set_enabled(true).recv()?; // Enable motor power

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;

    // Stop motor before disabling motor power
    pdc.set_motion(4096, 16384).recv()?; // Fast decceleration (50 %/s) for stopping
    pdc.set_velocity(0).recv()?; // Request motor stop
    thread::sleep(Duration::from_millis(2000)); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
    pdc.set_enabled(false).recv()?; // Disable motor power

    ipcon.disconnect();
    Ok(())
}
