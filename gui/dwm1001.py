#!/usr/bin/python3
import argparse
import struct
import time
from serial import Serial

class DwmDeviceManager():
    def __init__(self, adapter_name="/dev/ttyACM0"):
        Serial(adapter_name, 115200).close()
        time.sleep(0.1)
        self.dev = Serial(adapter_name, 115200)

    def _read_location(self):
        msg= self.dev.read_until()
        msg2 = "".join([chr(c) for c in msg])
        self.data = msg2.split()
       

    def run(self):
        self._read_location()
        # print (self.data)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("--port", type=str, default= "/dev/ttyACM0", help="Bluetooth adapter to use")

    args = parser.parse_args()
    port= args.port

    print("Reading location data from: {0}".format(port))
    manager = DwmDeviceManager(adapter_name=args.port)
    while 1:
        manager.run()

        
