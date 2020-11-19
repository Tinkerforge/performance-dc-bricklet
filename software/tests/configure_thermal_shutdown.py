#!/usr/bin/env python3
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "2aAi1w"

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_performance_dc import BrickletPerformanceDC
import time

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    dc = BrickletPerformanceDC(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    dc.set_thermal_shutdown(30)
    while True:
        temperature = dc.get_thermal_shutdown()
        print('{0} °C'.format(temperature))
        time.sleep(0.1)

    ipcon.disconnect()
