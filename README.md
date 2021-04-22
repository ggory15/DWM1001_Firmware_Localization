# DWM1001 Firmware for Localization

**NOTE: This set of projects require Seggar Embedded Studio.**  

This project contains examples on how to use the Ultra Wideband (UWB) and Bluetooth hardware based DWM1001 module together with FREERTOS from Seggar Embedded Studio. Specifically, this repository is the one of examples to esimate tag's position through triangulation between a tag and anchors. Thus, to run this example, you need at least four dwm1001 board (1 tag, 3 anchors).

This repository is based on 
* https://github.com/Decawave/dwm1001-examples (for DWM Firmware example)
* https://github.com/amalabey/dwm1001-gatt-client (for GUI)

The major changes from these original sources are:
* Write example code for localization with trianulation. 
* Change many lines to build it on Zephyr RTOS 2.5. 
* Make GUI with our custum BLE communication. 

If you wanna more insight about DWM firmware, you should visit above repositories. Then, you can find other examples. 

## Getting Started

## What's required?
### OS
Linux 18.04 
(I tested it on only Linux. But, I think it will be run if you install python3.x and Segger Embedded Studio on Windows and Mac OS.)

### Hardware
'DWM1001-dev', 'DWM1001c', 'MDEK1001'.
But, again, to run this example, you need at least four boards.

### Software 
* Seggar Embedded Studio (to build the firmware):
Follow the instructions for installation [here](https://www.segger.com/products/development-tools/embedded-studio/)

* wxPython (for GUI):
```
pip install -U -f https://extras.wxpython.org/wxPython4/extras/linux/gtk3/ubuntu-18.04/ wxPython
sudo apt-get install git curl libsdl2-mixer-2.0-0 libsdl2-image-2.0-0 libsdl2-2.0-0
```

## Download of Tag's Firmware
This firmware has the following functions
* Distance estimation between tag and each anchors (default: 3)

You can find source code of the tag's firmware, as follow:
```
cd apps/ss_initiator
```

NOTE: The firmware of Tag is to communicate with each anchors (default, three anchors). If you wanna change the number of anchors, please modify the following line in ss_init_main.c
```
#define NUM_ANCHOR 3
``` 

## Download of Anchor's Firmware
There are two different firmware for anchor
1) ss_respondor_master
  : This is for master anchor (the first anchor) to transfer distance information through UART.
2) ss_respondor_slave
  : This is for slave anchor (the second, third anchors)
  : There is no UART communication.
 
This firmware has the following function
* Communication btw tag

You can find source code of the anchor's firmware, as follow:
```
cd apps/ss_respondor_master (or ss_respondor_slave)
```

NOTE: The firmware of each anchors has id. So you should change the id of each anchor in ss_resp_slave.c. 
```
int my_id = 2; //2, 3 
```

## GUI
If you succesfully run a tag and anchors, you can use GUI system which is based on https://github.com/amalabey/dwm1001-gatt-client

To operate GUI, the first step is connecting master anchor with the computer (using microUSB) or arduino (using rx, tx pin). Then,
```
cd gui
sudo python3 main.py
```
Then you can find this window on your computer
![image](/gui/demo/demo-image.jpeg)






