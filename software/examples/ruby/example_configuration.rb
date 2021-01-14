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

pdc.set_drive_mode BrickletPerformanceDC::DRIVE_MODE_DRIVE_COAST
pdc.set_pwm_frequency 10000 # Use PWM frequency of 10 kHz
pdc.set_motion 4096, 4096 # Slow ac-/deceleration (12.5 %/s)
pdc.set_velocity 32767 # Full speed forward (100 %)
pdc.set_enabled true # Enable motor power

puts 'Press key to exit'
$stdin.gets

# Stop motor before disabling motor power
pdc.set_motion 4096, 16384 # Fast decceleration (50 %/s) for stopping
pdc.set_velocity 0 # Request motor stop
sleep 2 # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
pdc.set_enabled false # Disable motor power

ipcon.disconnect
