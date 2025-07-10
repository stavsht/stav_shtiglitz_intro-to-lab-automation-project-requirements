#include <Wire.h>
#include <Arduino_SensorKit.h>   
#include <Servo.h>

/*  pin map required by the assignment  */
const uint8_t SERVO_PIN  = 3;    // 
const uint8_t FAN_PIN    = 7;    // MOSFET gate – on/off only
const uint8_t BUZZER_PIN = 5;    // active buzzer

const float   THRESHOLD_DEG = 10.0;   // shut-off angle
const uint16_t LOOP_MS = 5000;          // screen & CSV refresh

Servo fanServo;
bool  buzzerOn = false;

/* ---------- setup ---------- */
void setup() {
  Serial.begin(9600);
  Wire.begin();

  /* initialise Sensor-Kit modules */
  Accelerometer.begin();   // MPU-6050 on the shield
  Oled.begin();                     // SSD1306 display

  fanServo.attach(SERVO_PIN);

  pinMode(FAN_PIN,    OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(FAN_PIN, HIGH);      // fan initially on
}

/* ---------- main loop ---------- */
void loop() {
  static uint32_t t0 = 0;
  if (millis() - t0 < LOOP_MS) return;
  t0 = millis();

  /* read acceleration and compute pitch */
  float ax = Accelerometer.readX();
  float ay = Accelerometer.readY();
  float az = Accelerometer.readZ();
  float angleDeg = atan2(ay, az) * 180.0 / PI;

  /* safety logic */
  if (abs(angleDeg) > THRESHOLD_DEG) {
    if (!buzzerOn) {
      buzzerOn = true;
      tone(BUZZER_PIN, 1000, 1000);
      digitalWrite(FAN_PIN,   LOW);    // stop fan
    }
  } else {
    if (buzzerOn) {
      buzzerOn = false;
      noTone(BUZZER_PIN);
      digitalWrite(FAN_PIN,   HIGH);   // restart fan
    }
    int s = map(
    constrain(angleDeg, -30, 30),   
    -30, 30,                    // input range
    45, 125                     // physical servo end-points
);
    fanServo.write(s);
  }

  /* OLED readout */
  Oled.clear();
  Oled.setCursor(0, 0);
  Oled.print(angleDeg, 1);  Oled.println(" deg");
  Oled.println(buzzerOn ? "ON" : "OFF");
  Oled.display();

  /* CSV stream for Python logger */
  Serial.print(millis());        Serial.print(',');
  Serial.print(angleDeg, 1);     Serial.print(',');
  Serial.println(buzzerOn ? 1 : 0);
}
