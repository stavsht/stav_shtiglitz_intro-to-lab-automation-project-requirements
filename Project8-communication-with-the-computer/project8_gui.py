"""
Project 8 GUI talks to project8.ino over the serial port.
----------------------------------------------------------
* Enter a duration in ms, click Send. Adds newline as required.
* Background thread reads serial responses and updates the GUI.
"""

import threading
import serial
import PySimpleGUI as sg

# ---------- serial settings ----------
PORT = 'COM5'         
BAUD = 9600 
ser = serial.Serial(PORT, BAUD, timeout=0.1)

# ---------- helper: push serial text into GUI ----------
def serial_listener(window):
    while True:
        try:
            if ser.in_waiting:
                line = ser.readline().decode(errors='replace').strip()
                # Translate numeric status codes
                if line == '0':
                    msg = 'LED off'
                elif line == '1':
                    msg = 'Button pressed - LED on'
                elif line == '2':
                    msg = 'Button released'
                else:
                    msg = line                  # Echo any other reply
                window.write_event_value('-MSG-', msg)
        except serial.SerialException as e:
            window.write_event_value('-MSG-', f'Serial error: {e}')
            break

# ---------- PySimpleGUI layout ----------
sg.theme('SystemDefault')
layout = [
    [sg.Text('LED-on time (ms):'),
     sg.Input(key='-TIME-', size=(10, 1)),
     sg.Button('Send')],
    [sg.Multiline(key='-OUT-', size=(60, 12), disabled=True)]
]
window = sg.Window('Project 8 - LED timer', layout, finalize=True)

# Start background listener
threading.Thread(target=serial_listener,
                 args=(window,),
                 daemon=True).start()

# ---------- main event loop ----------
while True:
    event, values = window.read()
    if event == sg.WIN_CLOSED:
        break

    if event == 'Send':
        t = values['-TIME-'].strip()
        if t.isdigit() and int(t) > 0:
            ser.write((t + '\n').encode())
            window['-OUT-'].print(f'Sent: {t} ms')
        else:
            window['-OUT-'].print('Enter a positive integer.')

    if event == '-MSG-':                       # From background thread
        window['-OUT-'].print(values[event])

ser.close()
window.close()
