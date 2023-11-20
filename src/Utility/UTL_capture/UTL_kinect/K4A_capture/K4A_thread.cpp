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

  if(!thread_running){
    this->thread = std::thread(&K4A_thread::run_capture, this, device);
  }

  //---------------------------
}

//Subfunction
void K4A_thread::run_capture(Struct_k4a_device* device){
  if(device == nullptr) return;
  //---------------------------

  //Init
  k4a::device k4a_device = k4a::device::open(device->index);
  k4a::capture k4a_capture;
  device->color.device = &k4a_device;
  device->color.capture = &k4a_capture;

  //Start recording
  k4a_device.start_cameras(&device->config.k4a_config);

  this->thread_running = true;
  std::chrono::milliseconds timeout(2000);
  while(thread_running){
    k4a_device.get_capture(&k4a_capture, timeout);
    device->temperature = k4a_capture.get_temperature_c();
    say(temp);
  }

  k4a_device.stop_cameras();

  device->color.device = nullptr;
  device->color.capture = nullptr;

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
