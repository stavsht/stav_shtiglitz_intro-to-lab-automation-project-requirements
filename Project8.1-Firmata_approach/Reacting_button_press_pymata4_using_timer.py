from pymata4 import pymata4
from threading import Timer
import time

BUTTON_PIN = 2
LED_PIN    = 4          
DELAY_MS   = 30

board = pymata4.Pymata4(com_port="COM5")       # explicit port is fine
led_timer = None

def turn_led_off():
    board.digital_write(LED_PIN, 0)
    print("LED off")

def cb(data):
    global led_timer
    pressed = data[2] == 1      # HIGH means pressed
    if pressed:
        print("Button pressed – LED on")
        board.digital_write(LED_PIN, 1)
        if led_timer and led_timer.is_alive():
            led_timer.cancel()
        led_timer = Timer(DELAY_MS / 1000, turn_led_off)
        led_timer.start()
    else:
        print("Button released")

board.set_pin_mode_digital_input(BUTTON_PIN, callback=cb)
board.set_pin_mode_digital_output(LED_PIN)

print("Ready – press the hardware button")
try:
    while True:
        time.sleep(0.1)             # keep main thread alive
except KeyboardInterrupt:
    print("\nExiting")
finally:
    board.shutdown()
