#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Performance DC Bricklet

tinkerforge call performance-dc-bricklet $uid set-drive-mode drive-mode-drive-coast
tinkerforge call performance-dc-bricklet $uid set-pwm-frequency 10000 # Use PWM frequency of 10 kHz
tinkerforge call performance-dc-bricklet $uid set-motion 4096 4096 # Slow ac-/deceleration (12.5 %/s)
tinkerforge call performance-dc-bricklet $uid set-velocity 32767 # Full speed forward (100 %)
tinkerforge call performance-dc-bricklet $uid set-enabled true # Enable motor power

echo "Press key to exit"; read dummy

# Stop motor before disabling motor power
tinkerforge call performance-dc-bricklet $uid set-motion 4096 16384 # Fast decceleration (50 %/s) for stopping
tinkerforge call performance-dc-bricklet $uid set-velocity 0 # Request motor stop
sleep 2 # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
tinkerforge call performance-dc-bricklet $uid set-enabled false # Disable motor power
