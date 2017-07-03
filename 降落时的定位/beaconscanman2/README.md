# Bluetooth iBeacon Scanner
A python script reads the information and writes it to a JSON file. A small node.js webserver displays the data in a browser. Optimized for the Raspberry Pi.

# Config on Raspbery Pi
```sh
sudo raspi-config (expand Filesystem)
sudo apt-get update
sudo apt-get upgrade
sudo apt-get install --no-install-recommends bluetooth
```
Followed the instructions on http://www.jaredwolff.com/blog/get-started-with-bluetooth-low-energy/

```sh
sudo apt-get install python-bluez
wget http://node-arm.herokuapp.com/node_latest_armhf.deb
sudo dpkg -i node_latest_armhf.deb
sudo apt-get install bc
```
