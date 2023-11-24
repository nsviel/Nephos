#include "Kinect.h"

#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_swarm.h>
#include <UTL_capture/UTL_kinect/K4A_capture/K4A_capture.h>
#include <UTL_capture/UTL_kinect/K4A_capture/K4A_replay.h>


//Constructor / Destructor
Kinect::Kinect(){
  //---------------------------

  this->struct_k4a_swarm = new Struct_k4a_swarm();
  this->k4a_swarm = new K4A_swarm(struct_k4a_swarm);

  //---------------------------
}
Kinect::~Kinect(){}

//Main function
void Kinect::init(){
  //---------------------------

  //Get actual connected device list
  k4a_swarm->refresh_connected_device_list();

  //Start capture accordingly
  if(struct_k4a_swarm->selected_device != nullptr){
    struct_k4a_swarm->selected_device->run_capture();
  }
  else{
    K4A_device* device = k4a_swarm->create_virtual_device("/home/aether/Desktop/output.mkv");
    struct_k4a_swarm->selected_device = device;
    device->run_replay();
  }

  //---------------------------
}
void Kinect::run_selected_device(){
  K4A_device* device = struct_k4a_swarm->selected_device;
  //---------------------------

  if(device != nullptr){
    device->run_capture();
  }

  //---------------------------
}
