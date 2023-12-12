#include "Kinect.h"

#include <Engine/Engine.h>


namespace eng::kinect{

//Constructor / Destructor
Kinect::Kinect(Engine* engine){
  //---------------------------


  this->k4a_swarm = new K4A_swarm(engine);
  this->k4a_connection = new eng::kinect::thread::Connection(k4a_swarm);

  //---------------------------
}
Kinect::~Kinect(){}

//Main function
void Kinect::init(){
  //---------------------------
//
  //Get actual connected device list
  k4a_swarm->refresh_connected_device_list();
  k4a_connection->start_thread();

  //Start capture accordingly
  K4A_device* selected_device = k4a_swarm->get_selected_device();
  if(selected_device != nullptr){
    //selected_device->run_capture();
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
  K4A_device* selected_device = k4a_swarm->get_selected_device();
  //---------------------------

  if(selected_device != nullptr){
    selected_device->run_capture();
  }

  //---------------------------
}

}
