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
# define println(x) Serial.println(x)

int LED1 = 4; // grove LED pin
int VarDelay = 1;
int BUTTON = 6; // Button pin


void setup() {
  // initialize digital pins as outputs.
  Serial.begin(9600); // Start serial communication for debugging
  pinMode(LED1, OUTPUT);
  pinMode(BUTTON, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(BUTTON) == HIGH) { // Check if button is pressed
    digitalWrite(LED1, HIGH); // Turn on LED1
    println("Button pressed, LED1 is ON");
  } else {
    digitalWrite(LED1, LOW); // Turn off LED1
  }
  delay(VarDelay);
  
  for (int i = 0; i< 10000; i++){
    println("calculating...");
}
}


