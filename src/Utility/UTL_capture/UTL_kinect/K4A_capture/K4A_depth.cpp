#include "K4A_depth.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>


//Constructor / Destructor
K4A_depth::K4A_depth(){
  //---------------------------

  this->struct_kinect = new Struct_kinect();

  //---------------------------
}
K4A_depth::~K4A_depth(){}

//Main function
void K4A_depth::find_depth_mode_range(){
  //---------------------------

  if(device->depth.mode == K4A_DEPTH_MODE_NFOV_2X2BINNED){
    device->depth.range_min = 500;
    device->depth.range_max = 5800;
  }
  else if(device->depth.mode == K4A_DEPTH_MODE_NFOV_UNBINNED){
    device->depth.range_min = 500;
    device->depth.range_max = 4000;
  }
  else if(device->depth.mode == K4A_DEPTH_MODE_WFOV_2X2BINNED){
    device->depth.range_min = 250;
    device->depth.range_max = 3000;
  }
  else if(device->depth.mode == K4A_DEPTH_MODE_WFOV_UNBINNED){
    device->depth.range_min = 250;
    device->depth.range_max = 2500;
  }

  //---------------------------
}
