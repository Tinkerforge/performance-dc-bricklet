function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletPerformanceDC;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Performance DC Bricklet

    ipcon = IPConnection(); % Create IP connection
    pdc = handle(BrickletPerformanceDC(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register velocity reached callback to function cb_velocity_reached
    set(pdc, 'VelocityReachedCallback', @(h, e) cb_velocity_reached(e));

    % Enable velocity reached callback
    pdc.setVelocityReachedCallbackConfiguration(true);

    % The acceleration has to be smaller or equal to the maximum
    % acceleration of the DC motor, otherwise the velocity reached
    % callback will be called too early
    pdc.setMotion(4096, 4096); % Slow acceleration (12.5 %/s)
    pdc.setVelocity(32767); % Full speed forward (100 %)

    % Enable motor power
    pdc.setEnabled(true);

    input('Press key to exit\n', 's');

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

    if e.velocity == 32767
        fprintf('Velocity: Full speed forward, now turning backward\n');
        pdc.setVelocity(-32767);
    elseif e.velocity == -32767
        fprintf('Velocity: Full speed backward, now turning forward\n');
        pdc.setVelocity(32767);
    else
        fprintf('Error\n'); % Can only happen if another program sets velocity
    end
end
