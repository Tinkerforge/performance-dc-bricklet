#!/usr/bin/env python3
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "2aAi1w"

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_performance_dc import BrickletPerformanceDC
import time

def cb_velocity_reached(velocity):
    print('Velocity Reached: {0}'.format(velocity))

def cb_emergency_shutdown():
    print('Thermal Shutdown')

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    dc = BrickletPerformanceDC(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    dc.register_callback(dc.CALLBACK_VELOCITY_REACHED, cb_velocity_reached)
    dc.register_callback(dc.CALLBACK_EMERGENCY_SHUTDOWN, cb_emergency_shutdown)

    dc.set_velocity_reached_callback_configuration(True)
    dc.set_emergency_shutdown_callback_configuration(True)

    input("Press key to exit\n")
    ipcon.disconnect()
