<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletPerformanceDC.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletPerformanceDC;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Performance DC Bricklet

$ipcon = new IPConnection(); // Create IP connection
$pdc = new BrickletPerformanceDC(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

$pdc->setDriveMode(BrickletPerformanceDC::DRIVE_MODE_DRIVE_COAST);
$pdc->setPWMFrequency(10000); // Use PWM frequency of 10 kHz
$pdc->setMotion(4096, 4096); // Slow ac-/deceleration (12.5 %/s)
$pdc->setVelocity(32767); // Full speed forward (100 %)
$pdc->setEnabled(TRUE); // Enable motor power

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));

// Stop motor before disabling motor power
$pdc->setMotion(4096, 16384); // Fast decceleration (50 %/s) for stopping
$pdc->setVelocity(0); // Request motor stop
sleep(2); // Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
$pdc->setEnabled(FALSE); // Disable motor power

$ipcon->disconnect();

?>
