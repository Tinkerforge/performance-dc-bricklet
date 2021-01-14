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
        pdc.setDriveMode(Tinkerforge.BrickletPerformanceDC.DRIVE_MODE_DRIVE_COAST);
        pdc.setPWMFrequency(10000); // Use PWM frequency of 10 kHz
        pdc.setMotion(4096, 4096); // Slow ac-/deceleration (12.5 %/s)
        pdc.setVelocity(32767); // Full speed forward (100 %)
        pdc.setEnabled(true); // Enable motor power
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
