#include "K4A_capture.h"


//Constructor / Destructor
K4A_capture::K4A_capture(){
  //---------------------------

  this->k4a_data = new util::kinect::data::Data();

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
void K4A_capture::run_thread(K4A_device* k4a_device){
  if(k4a_device == nullptr) return;
  //---------------------------

  //Init elements
  k4a::device device = k4a::device::open(k4a_device->index);
  k4a::capture capture;
  k4a::record recording;

  //Start camera
  k4a_device->config.version = device.get_version();
  device.start_cameras(&k4a_device->config.k4a_config);

  //Start recording
  if(is_recording){
    recording = k4a::record::create("output.mkv", device, k4a_device->config.k4a_config);
    recording.write_header();
  }

  //Start capture thread
  this->thread_running = true;
  while(thread_running && k4a_device){
    auto timeout = std::chrono::milliseconds(2000);
    device.get_capture(&capture, timeout);
    if(!capture) continue;

    //Recording
    if(is_recording) recording.write_capture(capture);

    //Capture data
    k4a_device->temperature = capture.get_temperature_c();
    k4a_data->find_data_from_capture(&k4a_device->data, capture);
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
