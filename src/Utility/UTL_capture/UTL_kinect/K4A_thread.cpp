#include "K4A_thread.h"
#include "Struct_kinect.h"


//Constructor / Destructor
K4A_thread::K4A_thread(Struct_kinect* struct_kinect){
  //---------------------------

  this->struct_kinect = struct_kinect;

  //---------------------------
}
K4A_thread::~K4A_thread(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void K4A_thread::start_thread(Struct_k4a_device* device){
  //---------------------------

  this->thread = std::thread(&K4A_thread::run_capture, this, device);

  //---------------------------
}

//Subfunction
void K4A_thread::run_capture(Struct_k4a_device* device){
  //---------------------------

  device->k4a_device->start_cameras(&struct_kinect->config.k4a_config);

  this->thread_running = true;
  std::chrono::milliseconds timeout;
  while(thread_running){
    device->k4a_device->get_capture(device->k4a_capture, timeout);
  }

  device->k4a_device->stop_cameras();

  //---------------------------
}
void K4A_thread::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
