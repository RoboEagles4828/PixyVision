from pixy import *
from ctypes import *
import socket
from subprocess import call
import time
import sys

def log(data):
    f = open("log.txt", "w")
    f.write(data)
    f.close()

log("started running")
call('sudo ./hello_pixy', shell=True)
print "Settings Loaded"
log("Settings Loaded")
time.sleep(0.1)

# Initialize Pixy Interpreter thread #
pixy_init()
print ("Initialized Pixy")
log("Initialized Pixy")
class Blocks (Structure):
  _fields_ = [ ("type", c_uint),
               ("signature", c_uint),
               ("x", c_uint),
               ("y", c_uint),
               ("width", c_uint),
               ("height", c_uint),
               ("angle", c_uint) ]

blocks = BlockArray(100)
frame  = 0

# Wait for blocks #

HOST = ''
PORT = 5800
soc = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
soc.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
soc.bind((HOST, PORT))
soc.listen(5)
conn, addr = soc.accept()
print("Got connection from", addr)
log("Got connection from")
test = pixy_get_blocks(100, blocks)
log("received data")
while 1:

  count = pixy_get_blocks(100, blocks)
  if count > 0:
    # Blocks found #
    print 'frame %3d:' % (frame)
    frame = frame + 1
    for index in range (0, count):
      print '[FRAME=%3d BLOCK_TYPE=%d SIG=%d X=%3d Y=%3d WIDTH=%3d HEIGHT=%3d]' % (frame, blocks[index].type, blocks[index].signature, blocks[index].x, blocks[index].y, blocks[index].width, blocks[index].height)
      output = []
      output.append(str(frame))
      output.append(str(blocks[index].type))
      output.append(str(blocks[index].signature))
      output.append(str(blocks[index].x))
      output.append(str(blocks[index].y))
      output.append(str(blocks[index].width))
      output.append(str(blocks[index].height))
      try:
        conn.send(" ".join(output) + "\n")
      except socket.error:
        conn.close()
        soc.listen(5)
        conn, addr = soc.accept()
        # print("Got connection from", addr)
        
        