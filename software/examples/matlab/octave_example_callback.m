function octave_example_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Performance DC Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    pdc = javaObject("com.tinkerforge.BrickletPerformanceDC", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register velocity reached callback to function cb_velocity_reached
    pdc.addVelocityReachedCallback(@cb_velocity_reached);

    % Enable velocity reached callback
    pdc.setVelocityReachedCallbackConfiguration(true);

    % The acceleration has to be smaller or equal to the maximum
    % acceleration of the DC motor, otherwise the velocity reached
    % callback will be called too early
    pdc.setMotion(4096, 4096); % Slow acceleration (12.5 %/s)
    pdc.setVelocity(32767); % Full speed forward (100 %)

    % Enable motor power
    pdc.setEnabled(true);

    input("Press key to exit\n", "s");

    % Stop motor before disabling motor power
    pdc.setMotion(4096, 16384); % Fast decceleration (50 %/s) for stopping
    pdc.setVelocity(0); % Request motor stop
    pause(2); % Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
    pdc.setEnabled(false); % Disable motor power

    ipcon.disconnect();
end

% Use velocity reached callback to swing back and forth
% between full speed forward and full speed backward
function cb_velocity_reached(e)
    pdc = e.getSource();
    velocity = short2int(e.velocity);

    if velocity == 32767
        fprintf("Velocity: Full speed forward, now turning backward\n");
        pdc.setVelocity(-32767);
    elseif velocity == -32767
        fprintf("Velocity: Full speed backward, now turning forward\n");
        pdc.setVelocity(32767);
    else
        fprintf("Error\n"); % Can only happen if another program sets velocity
    end
end

function int = java2int(value)
    if compare_versions(version(), "3.8", "<=")
        int = value.intValue();
    else
        int = value;
    end
end
