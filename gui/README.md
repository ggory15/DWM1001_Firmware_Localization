
echo "power on" | sudo bluetoothctl
sudo python3 dwm1001.py --discover
sudo python3 dwm1001.py --readlocation

