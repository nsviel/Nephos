#include "K4A_device.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_capture/K4A_capture.h>
#include <UTL_capture/UTL_kinect/K4A_capture/K4A_replay.h>


//Constructor / Destructor
K4A_device::K4A_device(){
  //---------------------------

  this->k4a_capture = new K4A_capture();
  this->k4a_replay = new K4A_replay();

  //---------------------------
}
K4A_device::~K4A_device(){}

//Main function
