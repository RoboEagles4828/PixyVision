#!/bin/bash

# delete log
sudo rm /home/pi/libpixyusb_swig/log.txt

# start pixy vision
cd /home/pi/libpixyusb_swig
sudo python get_blocks.py
