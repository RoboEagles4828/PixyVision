//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "pixy.h"

using namespace std;

#define BLOCK_BUFFER_SIZE    25

// Pixy Block buffer // 
struct Block blocks[BLOCK_BUFFER_SIZE];

static bool run_flag = true;

void handle_SIGINT(int unused)
{
  // On CTRL+C - abort! //

  run_flag = false;
}

int main(int argc, char * argv[])
{
  int      i = 0;
  int      index;
  int      blocks_copied;
  int      pixy_init_status;
  char     buf[128];

  // Catch CTRL+C (SIGINT) signals //
  signal(SIGINT, handle_SIGINT);

  //printf("Hello Pixy:\n libpixyusb Version: %s\n", __LIBPIXY_VERSION__);

  // Connect to Pixy //
  pixy_init_status = pixy_init();

  // Was there an error initializing pixy? //
  if(!pixy_init_status == 0)
  {
    // Error initializing Pixy //
    //printf("pixy_init(): ");
    pixy_error(pixy_init_status);

    return pixy_init_status;
  }

  // Request Pixy firmware version //
  {
    uint16_t major;
    uint16_t minor;
    uint16_t build;
    int      return_value;
    int32_t response;

    return_value = pixy_get_firmware_version(&major, &minor, &build);

    if (return_value) {
      // Error //
      //printf("Failed to retrieve Pixy firmware version. ");
      pixy_error(return_value);

      return return_value;
    } else {
      // Success //
      //printf(" Pixy Firmware Version: %d.%d.%d\n", major, minor, build);
    }
    return_value=pixy_command("cam_setWBV", UINT32(8013888),END_OUT_ARGS,  &response, END_IN_ARGS);
    //cout<<return_value<<endl;
    return_value=pixy_command("cam_setECV", UINT32(24832), END_OUT_ARGS,  &response, END_IN_ARGS);
    //cout<<return_value<<endl;
	return_value=pixy_command("cam_setBrightness", UINT8(26), END_OUT_ARGS,  &response, END_IN_ARGS);
	//cout<<return_value<<endl;
    return_value = pixy_command("cam_getWBV", END_OUT_ARGS, &response, END_IN_ARGS);
    //cout<<response<<endl;
    return_value = pixy_command("cam_getECV", END_OUT_ARGS, &response, END_IN_ARGS);
    //cout<<response<<endl;
    
  }
  pixy_close();
}