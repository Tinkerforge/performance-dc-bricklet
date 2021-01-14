Imports System
Imports System.Threading
Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your Performance DC Bricklet

    ' Use velocity reached callback to swing back and forth
    ' between full speed forward and full speed backward
    Sub VelocityReachedCB(ByVal sender As BrickletPerformanceDC, _
                          ByVal velocity As Short)
        If velocity = 32767 Then
            Console.WriteLine("Velocity: Full speed forward, now turning backward")
            sender.SetVelocity(-32767)
        Else If velocity = -32767 Then
            Console.WriteLine("Velocity: Full speed backward, now turning forward")
            sender.SetVelocity(32767)
        Else
            ' Can only happen if another program sets velocity
            Console.WriteLine("Error")
        End If
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim pdc As New BrickletPerformanceDC(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register velocity reached callback to subroutine VelocityReachedCB
        AddHandler pdc.VelocityReachedCallback, AddressOf VelocityReachedCB

        ' Enable velocity reached callback
        pdc.SetVelocityReachedCallbackConfiguration(True)

        ' The acceleration has to be smaller or equal to the maximum
        ' acceleration of the DC motor, otherwise the velocity reached
        ' callback will be called too early
        pdc.SetMotion(4096, 4096) ' Slow acceleration (12.5 %/s)
        pdc.SetVelocity(32767) ' Full speed forward (100 %)

        ' Enable motor power
        pdc.SetEnabled(True)

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
