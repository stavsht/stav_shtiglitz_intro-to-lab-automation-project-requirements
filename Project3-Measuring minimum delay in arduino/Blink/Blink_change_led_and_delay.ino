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
#define delayMicro delayMicroseconds
int LED_IN_USE = 4;
int VarDelay = 1;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_IN_USE, OUTPUT);
}
  pinMode(LED_IN_USE, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_IN_USE, HIGH);  // turn the LED on (HIGH is the voltage level)
  delayMicro(VarDelay);                      // wait for a second
  digitalWrite(LED_IN_USE, LOW);   // turn the LED off by making the voltage LOW
  delayMicro(VarDelay);                      // wait for a second
}

