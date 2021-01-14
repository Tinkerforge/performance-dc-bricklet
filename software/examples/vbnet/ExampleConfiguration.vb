Imports System
Imports System.Threading
Imports Tinkerforge

Module ExampleConfiguration
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your Performance DC Bricklet

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim pdc As New BrickletPerformanceDC(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        pdc.SetDriveMode(BrickletPerformanceDC.DRIVE_MODE_DRIVE_COAST)
        pdc.SetPWMFrequency(10000) ' Use PWM frequency of 10 kHz
        pdc.SetMotion(4096, 4096) ' Slow ac-/deceleration (12.5 %/s)
        pdc.SetVelocity(32767) ' Full speed forward (100 %)
        pdc.SetEnabled(True) ' Enable motor power

        Console.WriteLine("Press key to exit")
        Console.ReadLine()

        ' Stop motor before disabling motor power
        pdc.SetMotion(4096, 16384) ' Fast decceleration (50 %/s) for stopping
        pdc.SetVelocity(0) ' Request motor stop
        Thread.Sleep(2000) ' Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s
        pdc.SetEnabled(False) ' Disable motor power

        ipcon.Disconnect()
    End Sub
End Module
