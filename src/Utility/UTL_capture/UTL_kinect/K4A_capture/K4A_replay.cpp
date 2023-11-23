#include "K4A_replay.h"

#include <UTL_capture/UTL_kinect/Struct_kinect.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>


//Constructor / Destructor
K4A_replay::K4A_replay(Struct_kinect* struct_kinect){
  //---------------------------

  this->struct_kinect = struct_kinect;
  this->k4a_device = new K4A_device(struct_kinect);

  //---------------------------
}
K4A_replay::~K4A_replay(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void K4A_replay::start_thread(Struct_k4a_device* device){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&K4A_replay::run_capture, this, device);
  }

  //---------------------------
}

//Subfunction
void K4A_replay::run_capture(Struct_k4a_device* device){
  //---------------------------

  Struct_k4a_info playback;

  //Init
  k4a::playback recording = k4a::playback::open(device->info.path_file.c_str());

  this->thread_running = true;
  std::chrono::milliseconds timeout(2000);
  while(thread_running){
    k4a::capture next_capture;
    recording.get_next_capture(&next_capture);
    device->temperature = next_capture.get_temperature_c();
    device->data.capture = &next_capture;

    //Color
    k4a::image color = next_capture.get_color_image();
    device->data.color.name = "color";
    device->data.color.buffer = color.get_buffer();
    device->data.color.size = color.get_size();
    device->data.color.width = color.get_width_pixels();
    device->data.color.height = color.get_height_pixels();
    device->data.color.format = "B8G8R8A8_SRGB";
    device->data.color.timestamp = static_cast<float>(color.get_device_timestamp().count());
    color.reset();

    //Depth
    k4a::image depth = next_capture.get_depth_image();
    device->data.depth.name = "depth";
    device->data.depth.buffer = depth.get_buffer();
    device->data.depth.size = depth.get_size();
    device->data.depth.width = depth.get_width_pixels();
    device->data.depth.height = depth.get_height_pixels();
    device->data.depth.format = "B8G8R8A8_SRGB";
    device->data.depth.timestamp = static_cast<float>(depth.get_device_timestamp().count());
    depth.reset();

    //IR
    k4a::image ir = next_capture.get_ir_image();
    device->data.ir.name = "ir";
    device->data.ir.buffer = ir.get_buffer();
    device->data.ir.size = ir.get_size();
    device->data.ir.width = ir.get_width_pixels();
    device->data.ir.height = ir.get_height_pixels();
    device->data.ir.timestamp = static_cast<float>(ir.get_device_timestamp().count());
    ir.reset();

    device->data.data_ready = true;
  }

  //---------------------------
}
void K4A_replay::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
