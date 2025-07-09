/*
  Project 8 – two-way PC <-> Arduino link
  --------------------------------------
  States sent to the computer:
      0  LED off
      1  button pressed, LED on
      2  button released
*/

#include <MsTimer2.h>

const int LED_PIN       = 4;   // adjust if needed
const int BUTTON_PIN    = 2;   // must be an interrupt-capable pin
const unsigned long DEFAULT_MS = 1000UL;

volatile bool led_active = false;          // LED currently on?
volatile unsigned long hold_duration = DEFAULT_MS;

const unsigned long DEBOUNCE_MS = 25;
volatile unsigned long last_edge_time = 0;

// forward declarations
void turn_off();
void readSerialCommand();
void handleButtonEdge();

void setup() {
  Serial.begin(9600);                 // match this in Python

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);  

  // fire on both edges, decide inside the ISR whether it was press or release
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN),
                  handleButtonEdge,
                  CHANGE);

  Serial.println(0);                  // initial state – LED off
}

void loop() {
  readSerialCommand();                // parse any new duration sent by PC
}

/* ---------- serial command parser ---------- */
void readSerialCommand() {
  static String buffer;

  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {                  // end of number
      unsigned long val = buffer.toInt();
      if (val > 0) {
        hold_duration = val;
        Serial.print("I received: ");
        Serial.println(hold_duration);
      }
      buffer = "";
    } else if (isDigit(c)) {
      buffer += c;
    }
  }
}

/* ---------- interrupt routine ---------- */
void handleButtonEdge() {
  unsigned long now = millis();
  if (now - last_edge_time < DEBOUNCE_MS) return;   // debounce
  last_edge_time = now;

  bool pressed = digitalRead(BUTTON_PIN) == HIGH;   // HIGH means pressed
  if (pressed) {
    if (!led_active) {                // first press only
      led_active = true;
      digitalWrite(LED_PIN, HIGH);
      Serial.println(1);              // state 1: pressed, LED on

      MsTimer2::stop();
      MsTimer2::set(hold_duration + 1, turn_off);
      MsTimer2::start();
    }
  } else {                            // released
    Serial.println(2);                // state 2: button released
  }
}

/* ---------- timer callback ---------- */
void turn_off() {
  digitalWrite(LED_PIN, LOW);
  led_active = false;
  Serial.println(0);                  // state 0: LED off
}
