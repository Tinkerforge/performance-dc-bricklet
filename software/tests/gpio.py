#!/usr/bin/env python3
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "SB8"

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_performance_dc import BrickletPerformanceDC
import time

def cb_gpio_state(gpio_state):
    print(gpio_state)

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    dc = BrickletPerformanceDC(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    dc.register_callback(dc.CALLBACK_GPIO_STATE, cb_gpio_state)

    dc.set_gpio_action(0, dc.GPIO_ACTION_CALLBACK_RISING_EDGE)
    dc.set_gpio_action(1, dc.GPIO_ACTION_CALLBACK_FALLING_EDGE | dc.GPIO_ACTION_CALLBACK_RISING_EDGE)

    input("Press key to exit\n")
    ipcon.disconnect()
