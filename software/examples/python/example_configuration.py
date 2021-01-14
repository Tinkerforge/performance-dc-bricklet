#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your Performance DC Bricklet

import time

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_performance_dc import BrickletPerformanceDC

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    pdc = BrickletPerformanceDC(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    pdc.set_drive_mode(pdc.DRIVE_MODE_DRIVE_COAST)
    pdc.set_pwm_frequency(10000) # Use PWM frequency of 10 kHz
    pdc.set_motion(4096, 4096) # Slow ac-/deceleration (12.5 %/s)
    pdc.set_velocity(32767) # Full speed forward (100 %)
    pdc.set_enabled(True) # Enable motor power

    input("Press key to exit\n") # Use raw_input() in Python 2

    # Stop motor before disabling motor power
    pdc.set_motion(4096, 16384) # Fast decceleration (50 %/s) for stopping
    pdc.set_velocity(0) # Request motor stop
    time.sleep(2) # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
    pdc.set_enabled(False) # Disable motor power

    ipcon.disconnect()
