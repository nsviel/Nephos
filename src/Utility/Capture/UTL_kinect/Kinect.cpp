#include "Kinect.h"

#include <Utility/Capture/UTL_kinect/K4A_device/K4A_device.h>
#include <Utility/Capture/UTL_kinect/K4A_device/K4A_swarm.h>
#include <Utility/Capture/UTL_kinect/K4A_thread/K4A_connection.h>


namespace util::kinect{

//Constructor / Destructor
Kinect::Kinect(){
  //---------------------------

  this->struct_k4a_swarm = new Struct_k4a_swarm();
  this->k4a_swarm = new K4A_swarm(struct_k4a_swarm);
  this->k4a_connection = new K4A_connection(k4a_swarm);

  //---------------------------
}
Kinect::~Kinect(){}

//Main function
void Kinect::init(){
  //---------------------------

  //Get actual connected device list
  k4a_swarm->refresh_connected_device_list();
  k4a_connection->start_thread();

  //Start capture accordingly
  if(struct_k4a_swarm->selected_device != nullptr){
    //struct_k4a_swarm->selected_device->run_capture();
  }
  else{/*
    string path = "/home/aether/Desktop/output.mkv";
    //string path = "/home/aether/Desktop/francasque_4.mkv";
    K4A_device* device = k4a_swarm->create_device_virtual(path);
    this->set_selected_device(device);
    device->run_replay(path);*/
  }

  //---------------------------
}
void Kinect::restart_capture(){
  K4A_device* device = struct_k4a_swarm->selected_device;
  //---------------------------

  if(device != nullptr){
    device->run_capture();
  }

  //---------------------------
}

}
