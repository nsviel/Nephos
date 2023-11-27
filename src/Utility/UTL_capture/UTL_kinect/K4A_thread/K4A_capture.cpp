#include "K4A_capture.h"

#include <UTL_capture/UTL_kinect/K4A_data/K4A_data.h>


//Constructor / Destructor
K4A_capture::K4A_capture(){
  //---------------------------

  this->k4a_data = new K4A_data();

  //---------------------------
}
K4A_capture::~K4A_capture(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void K4A_capture::start_thread(K4A_device* device){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&K4A_capture::run_thread, this, device);
  }

  //---------------------------
}

//Subfunction
void K4A_capture::run_thread(K4A_device* device){
  if(device == nullptr) return;
  //---------------------------

  //Init
  k4a::device k4a_device = k4a::device::open(device->index);
  k4a::capture k4a_capture;
  k4a::record recording;

  //Start recording
  device->device = &k4a_device;
  device->config.version = k4a_device.get_version();

  k4a_device.start_cameras(&device->config.k4a_config);
  bool is_recording = thread_recording;
  if(is_recording){
    recording = k4a::record::create("output.mkv", k4a_device, device->config.k4a_config);
    recording.write_header();
  }

  this->thread_running = true;
  while(thread_running && device){
    if(!device){
      break;
    }

    k4a_device.get_capture(&k4a_capture, std::chrono::milliseconds(2000));
    if(!k4a_capture){
      continue;
    }

    if(is_recording){
      recording.write_capture(k4a_capture);
    }

    device->temperature = k4a_capture.get_temperature_c();
    k4a_data->find_data_from_capture(&device->data, k4a_capture);
  }

  if(is_recording){
    recording.flush();
  }

  //---------------------------
}
void K4A_capture::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
