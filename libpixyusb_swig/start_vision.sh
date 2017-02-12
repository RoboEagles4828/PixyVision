#!/bin/bash

# delete log
sudo rm /home/pi/PixyVision/libpixyusb_swig/log.txt

# start pixy vision
cd /home/pi/PixyVision/libpixyusb_swig
sudo python get_blocks.py
