# Arduino-stepper-motor-control-using-L293D-motor-driver

#Note:

For DC and stepper motor control, the shield makes use of pins D3, D4, D5, D6, D7, D8, D11, and D12.

#Wiring:

>> NEMA 17 bipolar stepper motors are rated at 12V and provide 200 steps per revolution. 
So, connect an external 12V power supply to the EXT_PWR terminal.
>> Connect forward and reverse push button pin with Arduino VCC (+5V) and same terminal connect it in Arduino GND using 10K resistor.
>> Don’t forget to remove the PWR jumper.
>> Finally, connect the motor to the stepper motor terminals M1-M2 (port #1) or M3-M4 (port #2). We are connecting it to M3-M4.

#Caution:

The NEMA 17 requires more current with microsteps than the L293D driver capabilities to produce more speed. So, if you need faster speed, please replace NEMA 17 with microstep driver. Otherwise, the L293D driver needs more current capacity or it may damaged.
