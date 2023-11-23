#include "K4A_replay.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_capture/K4A_capture.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>


//Constructor / Destructor
K4A_replay::K4A_replay(){
  //---------------------------

  this->struct_kinect = new Struct_kinect();
  this->k4a_capture = new K4A_capture(struct_kinect);
  this->k4a_device = new K4A_device(struct_kinect);

  //---------------------------
}
K4A_replay::~K4A_replay(){}

//Main function
void K4A_replay::run(){
  //---------------------------

  //---------------------------
}

//Subfunction
void K4A_replay::start_camera(){
  //---------------------------

  //---------------------------
}
