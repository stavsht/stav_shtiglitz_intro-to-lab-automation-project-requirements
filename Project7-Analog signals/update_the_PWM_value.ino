// This code reads an analog value from A0, maps it to a PWM value, and controls the brightness of an LED connected to pin 4.
#include <Arduino.h>
#include <MD_PWM.h>
#define println(x) Serial.println(x)

int LED1 = 4;             // Grove LED pin
int INTERRUPT_PIN = 2;    // Interrupt pin
int BUTTON = 6;           // Grove Button pin
int VarDelay = 1000;

MD_PWM ledPWM(LED1);      // Software PWM on pin 4

volatile bool interruptTriggered = false;

void handleInterrupt() {
  interruptTriggered = true;
}

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON, INPUT);
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);

  ledPWM.begin(30);         // Start PWM
  ledPWM.write(0);        // Start with LED off

  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), handleInterrupt, RISING);
}

void loop() {
  int analogValue = analogRead(A0);
  println(analogValue);

  int pwmValue = map(analogValue, 0, 1023, 0, 255);
  ledPWM.write(pwmValue);  // Set brightness

  if (interruptTriggered) {
    println("Interrupt: LED full");
    ledPWM.write(255);       // Full brightness
    delay(VarDelay);
    ledPWM.write(pwmValue);  // Restore brightness
    interruptTriggered = false;
  }

  delay(100);
}
