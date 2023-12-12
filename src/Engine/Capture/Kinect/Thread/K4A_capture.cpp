#include "K4A_capture.h"

#include <Engine/Engine.h>
#include <Utility/Function/Timer/FPS_counter.h>


//Constructor / Destructor
K4A_capture::K4A_capture(Engine* engine){
  //---------------------------

  this->fps_counter = new FPS_counter(60);
  this->k4a_data = new eng::kinect::data::Data();
  this->k4a_cloud = new eng::kinect::data::Cloud(engine);

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
  k4a::device device = k4a::device::open(k4a_device->device.index);
  k4a::capture capture;
  k4a::record recording;

  //Configuration
  k4a_device->device.device = &device;
  eng::kinect::configuration::make_k4a_configuration(k4a_device);
  eng::kinect::configuration::init_device_transformation(k4a_device);

  //Start camera
  k4a_device->device.version = device.get_version();
  device.start_cameras(&k4a_device->device.k4a_config);

  //Start recording
  if(is_recording){
    recording = k4a::record::create("output.mkv", device, k4a_device->device.k4a_config);
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
    k4a_data->find_data_from_capture(k4a_device, capture);
    k4a_cloud->convert_into_cloud(k4a_device);

    //FPS
    fps_counter->update();
    k4a_device->device.fps = fps_counter->get_fps();
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
