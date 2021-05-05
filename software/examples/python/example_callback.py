#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your Performance DC Bricklet

import time

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_performance_dc import BrickletPerformanceDC

# Use velocity reached callback to swing back and forth
# between full speed forward and full speed backward
def cb_velocity_reached(velocity, pdc):
    if velocity == 32767:
        print('Velocity: Full speed forward, now turning backward')
        pdc.set_velocity(-32767)
    elif velocity == -32767:
        print('Velocity: Full speed backward, now turning forward')
        pdc.set_velocity(32767)
    else:
        print('Error') # Can only happen if another program sets velocity

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    pdc = BrickletPerformanceDC(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Register velocity reached callback to function cb_velocity_reached
    pdc.register_callback(pdc.CALLBACK_VELOCITY_REACHED,
                          lambda x: cb_velocity_reached(x, pdc))

    # Enable velocity reached callback
    pdc.set_velocity_reached_callback_configuration(True)

    # The acceleration has to be smaller or equal to the maximum
    # acceleration of the DC motor, otherwise the velocity reached
    # callback will be called too early
    pdc.set_motion(4096, 4096) # Slow acceleration (12.5 %/s)
    pdc.set_velocity(32767) # Full speed forward (100 %)

    # Enable motor power
    pdc.set_enabled(True)

    input("Press key to exit\n") # Use raw_input() in Python 2

    # Stop motor before disabling motor power
    pdc.set_motion(4096, 16384) # Fast decceleration (50 %/s) for stopping
    pdc.set_velocity(0) # Request motor stop
    time.sleep(2) # Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
    pdc.set_enabled(False) # Disable motor power

    ipcon.disconnect()
