import serial
import time
import gi
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk
from sense_hat import SenseHat

ser = serial.Serial('/dev/ttyACM0', 115200)
sense = SenseHat()

sense.show_message("Hello World!")


class MyWindow(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="Hello World")

        self.button = Gtk.Button(label="Click Here")
        self.button.connect("clicked", self.on_button_clicked)
        self.add(self.button)

    def on_button_clicked(self, widget):
        print("Hello World")


win = MyWindow()
win.connect("delete-event", Gtk.main_quit)
win.show_all()
Gtk.main()

while True:
    ser.write(b'LMF025')
    time.sleep(5)
    ser.write(b'LMB025')
    time.sleep(5)
    ser.write(b'LST000')
    time.sleep(5)

