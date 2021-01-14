program ExampleCallback;

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
    procedure VelocityReachedCB(sender: TBrickletPerformanceDC; const velocity: smallint);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = 'XYZ'; { Change XYZ to the UID of your Performance DC Bricklet }

var
  e: TExample;

{ Use velocity reached callback to swing back and forth
  between full speed forward and full speed backward }
procedure TExample.VelocityReachedCB(sender: TBrickletPerformanceDC;
                                     const velocity: smallint);
begin
  if (velocity = 32767) then begin
    WriteLn('Velocity: Full speed forward, now turning backward');
    sender.SetVelocity(-32767);
  end
  else if (velocity = -32767) then begin
    WriteLn('Velocity: Full speed backward, now turning forward');
    sender.SetVelocity(32767);
  end
  else begin
    WriteLn('Error'); { Can only happen if another program sets velocity }
  end;
end;

procedure TExample.Execute;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  pdc := TBrickletPerformanceDC.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  { Register velocity reached callback to procedure VelocityReachedCB }
  pdc.OnVelocityReached := {$ifdef FPC}@{$endif}VelocityReachedCB;

  { Enable velocity reached callback }
  pdc.SetVelocityReachedCallbackConfiguration(true);

  { The acceleration has to be smaller or equal to the maximum
    acceleration of the DC motor, otherwise the velocity reached
    callback will be called too early }
  pdc.SetMotion(4096, 4096); { Slow acceleration (12.5 %/s) }
  pdc.SetVelocity(32767); { Full speed forward (100 %) }

  { Enable motor power }
  pdc.SetEnabled(true);

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
