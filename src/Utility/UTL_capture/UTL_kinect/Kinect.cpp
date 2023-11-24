#include "Kinect.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_swarm.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_configuration.h>
#include <UTL_capture/UTL_kinect/K4A_capture/K4A_capture.h>
#include <UTL_capture/UTL_kinect/K4A_capture/K4A_replay.h>


//Constructor / Destructor
Kinect::Kinect(){
  //---------------------------

  this->struct_kinect = new Struct_kinect();
  this->k4a_configuration= new K4A_configuration();
  this->k4a_swarm = new K4A_swarm(struct_kinect);

  //---------------------------
}
Kinect::~Kinect(){}

//Main function
void Kinect::init(){
  //---------------------------

  k4a_swarm->refresh_device_list();
  this->run();

  //---------------------------
}
void Kinect::run(){
  K4A_device* device = struct_kinect->selected_device;
  //---------------------------

  if(device != nullptr){
    k4a_configuration->make_k4a_configuration(device);
    device->k4a_capture->start_thread(device);
  }
  else{
    device = new K4A_device();
    struct_kinect->selected_device = device;
    device->info.file_path = "/home/aether/Desktop/output.mkv";
    device->k4a_replay->start_thread(device);
  }

  //---------------------------
}
