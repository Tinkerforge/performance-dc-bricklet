#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletPerformanceDC;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Performance DC Bricklet

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $pdc = Tinkerforge::BrickletPerformanceDC->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

$pdc->set_drive_mode($pdc->DRIVE_MODE_DRIVE_COAST);
$pdc->set_pwm_frequency(10000); # Use PWM frequency of 10 kHz
$pdc->set_motion(4096, 4096); # Slow ac-/deceleration (12.5 %/s)
$pdc->set_velocity(32767); # Full speed forward (100 %)
$pdc->set_enabled(1); # Enable motor power

print "Press key to exit\n";
<STDIN>;

# Stop motor before disabling motor power
$pdc->set_motion(4096, 16384); # Fast decceleration (50 %/s) for stopping
$pdc->set_velocity(0); # Request motor stop
sleep(2); # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
$pdc->set_enabled(0); # Disable motor power

$ipcon->disconnect();
