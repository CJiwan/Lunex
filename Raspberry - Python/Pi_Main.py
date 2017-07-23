import serial
import time
from sense_hat import SenseHat

ser = serial.Serial('/dev/ttyACM0', 115200)
sense = SenseHat()

sense.show_message("Hello World!")

while True:
    ser.write(b'LMF025')
    time.sleep(5)
    ser.write(b'LMB025')
    time.sleep(5)
    ser.write(b'LST000')
    time.sleep(5)
