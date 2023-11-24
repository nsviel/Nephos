#include "K4A_capture.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>
#include <UTL_capture/UTL_kinect/K4A_data/K4A_data.h>


//Constructor / Destructor
K4A_capture::K4A_capture(Struct_kinect* struct_kinect){
  //---------------------------

  this->struct_kinect = struct_kinect;
  this->k4a_device = new K4A_device(struct_kinect);
  this->k4a_data = new K4A_data(struct_kinect);

  //---------------------------
}
K4A_capture::~K4A_capture(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void K4A_capture::start_thread(Struct_k4a_device* device){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&K4A_capture::run_capture, this, device);
  }

  //---------------------------
}

//Subfunction
void K4A_capture::run_capture(Struct_k4a_device* device){
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
    recording.add_tag("Tag1", "Value1");
    recording.write_header();
  }

  this->thread_running = true;
  while(thread_running){
    k4a_device.get_capture(&k4a_capture, std::chrono::milliseconds(1000));
    device->temperature = k4a_capture.get_temperature_c();
    device->data.capture = &k4a_capture;

    if(is_recording){
      recording.write_capture(k4a_capture);
    }

    k4a_data->find_data_from_capture(&device->data, k4a_capture);
  }

  k4a_device.stop_cameras();

  device->data.capture = nullptr;

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
