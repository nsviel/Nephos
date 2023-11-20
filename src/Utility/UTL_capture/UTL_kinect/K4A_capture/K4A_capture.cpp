#include "K4A_capture.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_capture/K4A_thread.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>


//Constructor / Destructor
K4A_capture::K4A_capture(){
  //---------------------------

  this->struct_kinect = new Struct_kinect();
  this->k4a_thread = new K4A_thread(struct_kinect);
  this->k4a_device = new K4A_device(struct_kinect);

  //---------------------------
}
K4A_capture::~K4A_capture(){}

//Main function
void K4A_capture::run(){
  //---------------------------

  //---------------------------
}

//Subfunction
void K4A_capture::start_camera(){
  //---------------------------

  //---------------------------
}
