
# This code reads data from an Arduino via serial communication and logs it to a CSV file.

import csv, serial, time
ser = serial.Serial('COM5', 9600)
with open('fan_log.csv','w',newline='',buffering=1) as f:
    w = csv.writer(f)
    w.writerow(['pc_time_iso', 'arduino_ms', 'angle_deg', 'buzzer'])
    while True:
        line = ser.readline().decode().strip()
        if not line:
            continue
        ard_ms, angle, buzz = line.split(',')
        w.writerow([time.strftime('%Y-%m-%d %H:%M:%S'), ard_ms, angle, buzz])