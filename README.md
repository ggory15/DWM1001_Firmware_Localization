# DWM1001 Firmware for Localization (1 Tag and 3 Anchors)

**NOTE: This set of projects require Zephyr Version 2.5.**  
**      This also implies that zephyr-sdk-0.11.1 be installed or updated. **

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

* Gatt Client (for BLE communication):
```
sudo pip3 install gatt
sudo apt-get install python3-dbus
```
[Reference](https://github.com/getsenic/gatt-python)

