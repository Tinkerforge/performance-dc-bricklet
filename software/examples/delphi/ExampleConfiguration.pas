program ExampleConfiguration;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickletPerformanceDC;

type
  TExample = class
  private
    ipcon: TIPConnection;
    pdc: TBrickletPerformanceDC;
  public
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'XYZ'; { Change XYZ to the UID of your Performance DC Bricklet }

var
  e: TExample;

procedure TExample.Execute;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  pdc := TBrickletPerformanceDC.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  pdc.SetDriveMode(BRICKLET_PERFORMANCE_DC_DRIVE_MODE_DRIVE_COAST);
  pdc.SetPWMFrequency(10000); { Use PWM frequency of 10 kHz }
  pdc.SetMotion(4096, 4096); { Slow ac-/deceleration (12.5 %/s) }
  pdc.SetVelocity(32767); { Full speed forward (100 %) }
  pdc.SetEnabled(true); { Enable motor power }

  WriteLn('Press key to exit');
  ReadLn;

  { Stop motor before disabling motor power }
  pdc.SetMotion(4096, 16384); { Fast decceleration (50 %/s) for stopping }
  pdc.SetVelocity(0); { Request motor stop }
  Sleep(2000); { Wait for motor to actually stop: velocity (100 %) / decceleration (50 %/s) = 2 s }
  pdc.SetEnabled(false); { Disable motor power }

  ipcon.Destroy; { Calls ipcon.Disconnect internally }
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
