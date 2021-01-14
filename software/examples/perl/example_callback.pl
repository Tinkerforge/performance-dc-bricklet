#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletPerformanceDC;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Performance DC Bricklet

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
our $pdc = Tinkerforge::BrickletPerformanceDC->new(&UID, $ipcon); # Create device object

# Use velocity reached callback to swing back and forth
# between full speed forward and full speed backward
sub cb_velocity_reached
{
    my ($velocity) = @_;

    if ($velocity == 32767)
    {
        print "Velocity: Full speed forward, now turning backward\n";
        $pdc->set_velocity(-32767);
    }
    elsif ($velocity == -32767)
    {
        print "Velocity: Full speed backward, now turning forward\n";
        $pdc->set_velocity(32767);
    }
    else
    {
        print "Error\n"; # Can only happen if another program sets velocity
    }
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register velocity reached callback to subroutine cb_velocity_reached
$pdc->register_callback($pdc->CALLBACK_VELOCITY_REACHED, 'cb_velocity_reached');

# Enable velocity reached callback
$pdc->set_velocity_reached_callback_configuration(1);

# The acceleration has to be smaller or equal to the maximum
# acceleration of the DC motor, otherwise the velocity reached
# callback will be called too early
$pdc->set_motion(4096, 4096); # Slow acceleration (12.5 %/s)
$pdc->set_velocity(32767); # Full speed forward (100 %)

# Enable motor power
$pdc->set_enabled(1);

print "Press key to exit\n";
<STDIN>;

# Stop motor before disabling motor power
$pdc->set_motion(4096, 16384); # Fast decceleration (50 %/s) for stopping
$pdc->set_velocity(0); # Request motor stop
sleep(2); # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
$pdc->set_enabled(0); # Disable motor power

$ipcon->disconnect();
