// This code reads an analog value from A0, maps it to a PWM value, and controls the angle of the servo.
#include <Arduino.h>
#include <MD_PWM.h>
#define println(x) Serial.println(x)
#include <Servo.h>
Servo myServo;

int LED1 = 4;             // Grove LED pin
int INTERRUPT_PIN = 2;    // Interrupt pin
int BUTTON = 6;           // Grove Button pin
int VarDelay = 1000;
int PWM_FREQUENCY = 50; // Frequency for PWM, can be changed to 50Hz if needed
int SERVO_PIN = 7;       // Servo pin


MD_PWM ledPWM(LED1);      // Software PWM on pin 4

volatile bool interruptTriggered = false;

void handleInterrupt() {
  interruptTriggered = true;
}

void setup() {
  Serial.begin(9600);
  myServo.attach(SERVO_PIN);
  pinMode(BUTTON, INPUT);
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);

  ledPWM.begin(PWM_FREQUENCY);         // Start PWM
  ledPWM.write(0);        // Start with LED off

  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), handleInterrupt, RISING);
}

void loop() {
  int analogValue = analogRead(A0);
  println(analogValue);

  int angle = map(analogValue, 0, 1023, 0, 180);
  myServo.write(angle);

  delay(100);
}

