// This code uses an interrupt to toggle the state of an LED when a button is pressed.
// It also reads a potentiometer value and prints it to the serial monitor.
#include <Arduino.h>
#define println(x) Serial.println(x)

int LED1 = 4;            // LED pin
int INTERRUPT_PIN = 2;   // Interrupt pin (must be 2 or 3 on Uno)
int BUTTON = 6;          // Grove Button pin
int VarDelay = 1000;     // Delay time in milliseconds

void handleInterrupt() {
  println("working");
  digitalWrite(LED1, HIGH);
}

void setup() {
  Serial.begin(9600);

  pinMode(LED1, OUTPUT);
  pinMode(BUTTON, INPUT); 
  pinMode(INTERRUPT_PIN, INPUT_PULLUP); // Button input with internal pull-up

  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), handleInterrupt, RISING);
}

void loop() {
  int analogValue = analogRead(A0); // Read potentiometer value (0 to 1023)
  println(analogValue);             // Print value to serial monitor
  delay(100);                       // Short delay to slow down printing

  // Optional: keep your existing button code if needed
  if (digitalRead(BUTTON) == HIGH) {
    println("LED ON by interrupt");
    digitalWrite(LED1, HIGH);
    delay(VarDelay);
    digitalWrite(LED1, LOW);
  }
}
