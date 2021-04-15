# DWM1001 Firmware for Localization

**NOTE: This set of projects require Zephyr Version 2.5.**  

This project contains examples on how to use the Ultra Wideband (UWB) and Bluetooth hardware based DWM1001 module together with Zephyr RTOS. Specifically, this repository is the one of examples to esimate tag's position through triangulation between a tag and anchors. Thus, to run this example, you need at least four dwm1001 board (1 tag, 3 anchors).

This repository is based on 
* https://github.com/foldedtoad/dwm1001 (for DWM Firmware with Zephyr)
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
(I tested it on only Linux. But, I think it will be run if you install python3.x and Zephyr on Windows and Mac OS.)

### Hardware
'DWM1001-dev', 'DWM1001c', 'MDEK1001'.
But, again, to run this example, you need at least four boards.

### Software 
* Zephyr RTOS (to build the firmware):
Follow the instructions from Zephyr [here](https://docs.zephyrproject.org/latest/getting_started/index.html#set-up-a-development-system)

* nRF-Command-Line-Tools_10_12_1_Linux-amd64 (to download the frimware to the board):
You can find it [here]
(https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF5-Command-Line-Tools)

* wxPython (for GUI):
```
pip install -U -f https://extras.wxpython.org/wxPython4/extras/linux/gtk3/ubuntu-18.04/ wxPython
sudo apt-get install git curl libsdl2-mixer-2.0-0 libsdl2-image-2.0-0 libsdl2-2.0-0
```

* Gatt Client (for BLE communication) [Reference](https://github.com/getsenic/gatt-python):
```
sudo pip3 install gatt
sudo apt-get install python3-dbus
```
## Download of Tag's Firmware
This firmware has the following functions
* Distance estimation between tag and each anchors (default: 3)
* BLE communication between tag and other device (such as computer, RasberryPi, etc)

You can find source code of the tag's firmware, as follow:
```
cd apps/ss_initiator
```
To build this example
```
mkdir build
cd build
make
```
To Download this example to your DWM board
```
make flash
```
NOTE: If you get error messages from the above procedure, you should check your Zephyr RTOS version.

NOTE: The firmware of Tag is to communicate with each anchors (default, three anchors). If you wanna change the number of anchors, please modify the following line in main.c
```
#define NUM_ANCHOR 3
``` 
Note: The BLE(Bluetooth Low Energy)'s name is automatically set as "DWM1001_TAG". 
And the default Cahracterisitcs UUID is de259bcd-1d7c-48db-a7e3-4759ac040002 
## Download of Tag's Firmware
This firmware has the following function
* Communication btw tag
You can find source code of the tag's firmware, as follow:
```
cd apps/ss_respondor
```
To build this example
```
mkdir build
cd build
make
```
To Download this example to your DWM board
```
make flash
```
NOTE: If you get error messages from the above procedure, you should check your Zephyr RTOS version.

NOTE: The firmware of each anchors has id. So you should change the id of each anchor in main.c. 
```
int my_id = 1; //1, 2, 3 
```



