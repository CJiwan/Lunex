import serial
import time


ser = serial.Serial('/dev/ttyACM0', 115200)

while True:
    ser.write(b'LMF025')
    time.sleep(5)
    ser.write(b'LMB025')
    time.sleep(5)
    ser.write(b'LST000')
    time.sleep(5)