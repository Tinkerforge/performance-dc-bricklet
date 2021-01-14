function octave_example_configuration()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Performance DC Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    pdc = javaObject("com.tinkerforge.BrickletPerformanceDC", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    pdc.setDriveMode(pdc.DRIVE_MODE_DRIVE_COAST);
    pdc.setPWMFrequency(10000); % Use PWM frequency of 10 kHz
    pdc.setMotion(4096, 4096); % Slow ac-/deceleration (12.5 %/s)
    pdc.setVelocity(32767); % Full speed forward (100 %)
    pdc.setEnabled(true); % Enable motor power

    input("Press key to exit\n", "s");

    % Stop motor before disabling motor power
    pdc.setMotion(4096, 16384); % Fast decceleration (50 %/s) for stopping
    pdc.setVelocity(0); % Request motor stop
    pause(2); % Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
    pdc.setEnabled(false); % Disable motor power

    ipcon.disconnect();
end
