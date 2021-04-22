from serial import Serial
import numpy as np
import time
port = "/dev/ttyACM0"
Serial(port, 115200).close()
time.sleep(2)
dev = Serial(port, 115200)
np.set_printoptions(precision=3)

print("Start")
while True:
    print(dev.read_until())
