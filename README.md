# PixyVision

## Info
* We modified the code that came with the Pixy Camera starter files which is why the folder names and organization is weird, `hello_pixy` was supposed to be the C++ starter project and `libpixyusb_swig` was supposed to be the python starter project.
* This repository contains two folders, hello_pixy which contains code to interact with the pixycam through the C++ api and libpixyusb_swig which contains code to interact with the pixycam through the python api.
* Both were necessary when we tried to use the camera since we could not change the camera settings through the python code for some reason. Therefore in `hello_pixy/hello_pixy.cpp` we set the brightness, exposure and white balance of the camera.
* Next our python code in `libpixyusb_swig/get_blocks.py` sets up a network socket and transmits frame number, signature, width, height, x and y of the targets to the robot through the network socket. Network sockets are used because they are easy to implement in both Python and Java.

## Usage
* First follow the PixyCam documentation and set up a raspberry pi with the libraries for both the python and C++ APIs for the pixy
* Next run the `hello_pixy/build.sh` script to build the `hello_pixy` binary, the script also moves the binary to the libpixyusb_swig folder
* Then run the `libpixyusb_swig/start_vision.sh` script which runs the `get_blocks.py` script which in turn runs the `hello_pixy` binary and starts transmitting the detected targets over the network socket.

## Stuff that should be fixed
* This repository needs a `.gitignore`, it's full of build files and artifacts that shouldn't have been pushed.
* A more organized way of building and running everything which should probably be a `Makefile` or something similar but I didn't know how to use those when I first made these scripts.
