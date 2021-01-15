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

    let velocity_reached_receiver = pdc.get_velocity_reached_callback_receiver();

    // Spawn thread to handle received callback messages.
    // This thread ends when the `pdc` object
    // is dropped, so there is no need for manual cleanup.
    let pdc_copy = pdc.clone(); // Device objects don't implement Sync, so they can't be shared
                                // between threads (by reference). So clone the device and move the copy.
    thread::spawn(move || {
        for velocity_reached in velocity_reached_receiver {
            if velocity_reached == 32767 {
                println!("Velocity: Full speed forward, now turning backward");
                pdc_copy.set_velocity(-32767);
            } else if velocity_reached == -32767 {
                println!("Velocity: Full speed backward, now turning forward");
                pdc_copy.set_velocity(32767);
            } else {
                //can only happen if another program sets velocity
                panic!("Error");
            }
        }
    });

    // Enable velocity reached callback
    pdc.set_velocity_reached_callback_configuration(true).recv()?;

    // The acceleration has to be smaller or equal to the maximum
    // acceleration of the DC motor, otherwise the velocity reached
    // callback will be called too early
    pdc.set_motion(4096, 4096).recv()?; // Slow acceleration (12.5 %/s)
    pdc.set_velocity(32767).recv()?; // Full speed forward (100 %)

    // Enable motor power
    pdc.set_enabled(true).recv()?;

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
