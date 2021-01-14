#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_performance_dc'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your Performance DC Bricklet

ipcon = IPConnection.new # Create IP connection
pdc = BrickletPerformanceDC.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Use velocity reached callback to swing back and forth
# between full speed forward and full speed backward
pdc.register_callback(BrickletPerformanceDC::CALLBACK_VELOCITY_REACHED) do |velocity|
  if velocity == 32767
    puts 'Velocity: Full speed forward, now turning backward'
    pdc.set_velocity(-32767)
  elsif velocity == -32767
    puts 'Velocity: Full speed backward, now turning forward'
    pdc.set_velocity 32767
  else
    puts 'Error' # Can only happen if another program sets velocity
  end
end

# Enable velocity reached callback
pdc.set_velocity_reached_callback_configuration true

# The acceleration has to be smaller or equal to the maximum
# acceleration of the DC motor, otherwise the velocity reached
# callback will be called too early
pdc.set_motion 4096, 4096 # Slow acceleration (12.5 %/s)
pdc.set_velocity 32767 # Full speed forward (100 %)

# Enable motor power
pdc.set_enabled true

puts 'Press key to exit'
$stdin.gets

# Stop motor before disabling motor power
pdc.set_motion 4096, 16384 # Fast decceleration (50 %/s) for stopping
pdc.set_velocity 0 # Request motor stop
sleep 2 # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
pdc.set_enabled false # Disable motor power

ipcon.disconnect
