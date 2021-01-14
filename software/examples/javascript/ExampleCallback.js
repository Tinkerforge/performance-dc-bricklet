var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your Performance DC Bricklet

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var pdc = new Tinkerforge.BrickletPerformanceDC(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Enable velocity reached callback
        pdc.setVelocityReachedCallbackConfiguration(true);

        // The acceleration has to be smaller or equal to the maximum
        // acceleration of the DC motor, otherwise the velocity reached
        // callback will be called too early
        pdc.setMotion(4096, 4096); // Slow acceleration (12.5 %/s)
        pdc.setVelocity(32767); // Full speed forward (100 %)

        // Enable motor power
        pdc.setEnabled(true);
    }
);

// Register velocity reached callback
pdc.on(Tinkerforge.BrickletPerformanceDC.CALLBACK_VELOCITY_REACHED,
    // Use velocity reached callback to swing back and forth
    // between full speed forward and full speed backward
    function (velocity) {
        if(velocity == 32767) {
            console.log('Velocity: Full speed forward, now turning backward');
            pdc.setVelocity(-32767);
        }
        else if(velocity === -32767) {
            console.log('Velocity: Full speed backward, now turning forward');
            pdc.setVelocity(32767);
        }
        else {
            console.log('Error'); // Can only happen if another program sets velocity
        }
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        // Stop motor before disabling motor power
        pdc.setMotion(4096, 16384); // Fast decceleration (50 %/s) for stopping
        pdc.setVelocity(0); // Request motor stop

        setTimeout(function () {
            pdc.setEnabled(false); // Disable motor power

            ipcon.disconnect();
            process.exit(0);
        }, 2000); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
    }
);
