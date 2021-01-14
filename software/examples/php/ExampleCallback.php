<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletPerformanceDC.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletPerformanceDC;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Performance DC Bricklet

// Use velocity reached callback to swing back and forth
// between full speed forward and full speed backward
function cb_velocityReached($velocity, $user_data)
{
    $pdc = $user_data;

    if ($velocity == 32767) {
        echo "Velocity: Full speed forward, now turning backward\n";
        $pdc->setVelocity(-32767);
    } elseif ($velocity == -32767) {
        echo "Velocity: Full speed backward, now turning forward\n";
        $pdc->setVelocity(32767);
    } else {
        echo "Error\n"; // Can only happen if another program sets velocity
    }
}

$ipcon = new IPConnection(); // Create IP connection
$pdc = new BrickletPerformanceDC(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register velocity reached callback to function cb_velocityReached
$pdc->registerCallback(BrickletPerformanceDC::CALLBACK_VELOCITY_REACHED,
                       'cb_velocityReached', $pdc);

// Enable velocity reached callback
$pdc->setVelocityReachedCallbackConfiguration(TRUE);

// The acceleration has to be smaller or equal to the maximum
// acceleration of the DC motor, otherwise the velocity reached
// callback will be called too early
$pdc->setMotion(4096, 4096); // Slow acceleration (12.5 %/s)
$pdc->setVelocity(32767); // Full speed forward (100 %)

// Enable motor power
$pdc->setEnabled(TRUE);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
