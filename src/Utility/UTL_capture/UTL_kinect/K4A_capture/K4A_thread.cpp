#include "K4A_thread.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>


//Constructor / Destructor
K4A_thread::K4A_thread(Struct_kinect* struct_kinect){
  //---------------------------

  this->struct_kinect = struct_kinect;
  this->k4a_device = new K4A_device(struct_kinect);

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
void K4A_thread::run_capture(Struct_k4a_device* struc_device){
  if(struc_device == nullptr) return;
  //---------------------------

  k4a::device device = k4a::device::open(struc_device->index);
  device.start_cameras(&struc_device->config.k4a_config);

  this->thread_running = true;
  std::chrono::milliseconds timeout(2000);
  while(thread_running){
    device.get_capture(struc_device->k4a_capture, timeout);
  }

  device.stop_cameras();

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
