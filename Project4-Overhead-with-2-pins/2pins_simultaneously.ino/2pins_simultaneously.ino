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

void setup() {
  // Set PB4 and PB5 (digital pins 12 and 13) as output
  DDRB |= (1 << PB4) | (1 << PB5);
}

void loop() {
  // Set PB4 and PB5 high (turn LEDs on)
  PORTB |= (1 << PB4) | (1 << PB5);
  delay(1); // use delay in ms

  // Set PB4 and PB5 low (turn LEDs off)
  PORTB &= ~((1 << PB4) | (1 << PB5));
  delay(1);
}

