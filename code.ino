/*
#Note:
For DC and stepper motor control, the shield makes use of pins D3, D4, D5, D6, D7, D8, D11, and D12.

#Wiring:
>> NEMA 17 bipolar stepper motors are rated at 12V and provide 200 steps per revolution. 
So, connect an external 12V power supply to the EXT_PWR terminal.
>> Connect forward and reverse push button pin with Arduino VCC (+5V) and same terminal connect it in Arduino GND using 10K resistor.
>> Don’t forget to remove the PWR jumper.
>> Finally, connect the motor to the stepper motor terminals M1-M2 (port #1) or M3-M4 (port #2). We are connecting it to M3-M4.

#Caution:
The NEMA 17 requires more current with microsteps than the L293D driver capabilities to produce more speed. So, if you need faster speed, please replace NEMA 17 with microstep driver.
Otherwise, the L293D driver needs more current capacity or it will be damaged.
*/


#include <AFMotor.h>

#define STEP_PER_REVOLUTION 200 // set steps per revolution
#define SPEED 10    // set stepper motor speed in RPM

#define FORWARD_PIN A0            // set an input push button as a forward switch
#define REVERSE_PIN A1          // set an input push buton as a backward switch
#define TARGET_STEPS 100       // set how many steps will rotate the motor when pressed forward or backward switch

// to motor port #2 (M3 and M4)
AF_Stepper motor(STEP_PER_REVOLUTION, 2); // if you want to use M1 and M2 set the value #1

unsigned char terminal_command; // character type variable to receive data from serial command

void setup() {
  // serial port initialize
  Serial.begin(9600);
  
  motor.setSpeed(SPEED); // set motor speed

  pinMode(FORWARD_PIN, INPUT);
  pinMode(REVERSE_PIN, INPUT);

  Serial.println("Initialize Completed!");
}

void loop() {
  int forward_state = digitalRead(FORWARD_PIN);   // read the forward push button
  if (forward_state == HIGH) {
    motor.step(TARGET_STEPS, FORWARD, MICROSTEP); // run in forward mode
  }

  int reverse_state = digitalRead(REVERSE_PIN);   // read the reverse push button
  if (reverse_state == HIGH) {
    motor.step(TARGET_STEPS, BACKWARD, MICROSTEP);  // run in reverse mode
  }

  // send small letter "f" to move the stepper in forward
  // send small letter "r" to move the stepper in backward

  if (Serial.available()) {

    terminal_command = Serial.read(); // receive data from serial command
    
    Serial.println(terminal_command);
    switch (terminal_command) {
      case 102:
        Serial.println("f");
        motor.step(TARGET_STEPS, FORWARD, MICROSTEP);   // run in forward mode
        break;

      case 114:
        Serial.println("r");
        motor.step(TARGET_STEPS, BACKWARD, MICROSTEP);    // run in reverse mode
        break;

      default:
        break;
    }
  }
}