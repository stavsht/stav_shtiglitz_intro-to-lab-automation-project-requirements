"""
Reacting_button_press_pymata4_gui.py
------------------------------------
Adds a FreeSimpleGUI front-end:
• Shows real-time button state.
• Lets the user type a new LED-on duration in ms.
"""

import queue
from threading import Timer, Thread
from pymata4 import pymata4
import PySimpleGUI as sg
import time

BUTTON_PIN = 2
LED_PIN = 4
DEFAULT_MS = 30

# ----- shared objects -----
board = pymata4.Pymata4()
gui_queue = queue.Queue()
led_off_timer = None
delay_ms = DEFAULT_MS

# ----- Arduino callback -----
def button_callback(data):
    global led_off_timer
    pressed = data[2] == 1      # HIGH means pressed
    if pressed:
        board.digital_write(LED_PIN, 1)
        gui_queue.put("Button pressed - LED on")
        if led_off_timer and led_off_timer.is_alive():
            led_off_timer.cancel()
        led_off_timer = Timer(delay_ms / 1000, turn_led_off)
        led_off_timer.start()
    else:
        gui_queue.put("Button released")

def turn_led_off():
    board.digital_write(LED_PIN, 0)
    gui_queue.put("LED off")

# ----- background thread -----
def pymata_thread():
    board.set_pin_mode_digital_input(BUTTON_PIN, callback=button_callback)
    board.set_pin_mode_digital_output(LED_PIN)
    while True:
        time.sleep(0.1) 

Thread(target=pymata_thread, daemon=True).start()

# ----- GUI layout -----
sg.theme("SystemDefault")
layout = [
    [sg.Text("LED-on time (ms):"),
     sg.Input(str(DEFAULT_MS), key="-MS-", size=(6,1)),
     sg.Button("Update")],
    [sg.Multiline(key="-LOG-", size=(50,10), disabled=True)]
]
window = sg.Window("Pymata4 Button Demo", layout, finalize=True)

# ----- main GUI loop -----
try:
    while True:
        event, values = window.read(timeout=100)
        if event == sg.WIN_CLOSED:
            break
        if event == "Update":
            try:
                new_ms = int(values["-MS-"])
                if new_ms > 0:
                    delay_ms = new_ms
                    window["-LOG-"].print(f"New delay set: {delay_ms} ms")
            except ValueError:
                window["-LOG-"].print("Enter a positive integer")

        # drain messages from callback
        while not gui_queue.empty():
            window["-LOG-"].print(gui_queue.get_nowait())

finally:
    board.shutdown()
    window.close()
