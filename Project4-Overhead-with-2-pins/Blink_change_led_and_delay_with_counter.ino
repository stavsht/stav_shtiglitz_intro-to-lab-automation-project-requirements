/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/

#include <Arduino.h>

int LED1 = 13;
int VarDelay = 1;
int LED2 = 12;
int counter = 0; // New variable for calculation

void setup() {
  // initialize digital pins as outputs.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED1, HIGH);
  // Calculation: increment counter and store result
  int result = counter + 1;
  counter = result;
  digitalWrite(LED2, HIGH);

  delay(VarDelay);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  delay(VarDelay);
}


