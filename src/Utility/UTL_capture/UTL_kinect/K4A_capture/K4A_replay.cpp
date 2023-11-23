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

  //Init
  k4a::playback playback = k4a::playback::open(device->info.file_path.c_str());
  if (!playback) {
    cout<<"[error] Failed to open playback file"<<endl;
    return;
  }

  std::cout << "Playback duration: " << playback.get_recording_length().count() << " microseconds\n";

  k4a::capture next_capture;
  this->thread_running = true;
  while(playback.get_next_capture(&next_capture)){
    if (!next_capture) {
      cout<<"[error] Failed to get next capture"<<endl;
      break;
    }

    //Color
    k4a::image color = next_capture.get_color_image();
    if (!color) {continue;}
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

    device->data.data_ready = false;
    this->sleep_necessary_time(device);
  }

  //---------------------------
}
void K4A_replay::sleep_necessary_time(Struct_k4a_device* device){
  //---------------------------

  switch(device->config.fps){
    case K4A_FRAMES_PER_SECOND_5:{
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    case K4A_FRAMES_PER_SECOND_15:{
      std::this_thread::sleep_for(std::chrono::milliseconds(66));
    }
    case K4A_FRAMES_PER_SECOND_30:{
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
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
