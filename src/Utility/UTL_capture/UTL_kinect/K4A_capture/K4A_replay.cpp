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
void K4A_replay::start_thread(string path){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&K4A_replay::run_capture, this, path);
  }

  //---------------------------
}

//Subfunction
void K4A_replay::run_capture(string path){
  //---------------------------

  Struct_k4a_playback playback;

  //Init
  k4a::playback recording = k4a::playback::open(path.c_str());

  this->thread_running = true;
  std::chrono::milliseconds timeout(2000);
  while(thread_running){
    k4a::capture next_capture;
    recording.get_next_capture(&next_capture);
    playback.data.capture = &next_capture;

    //Color
    k4a::image color = next_capture.get_color_image();
    playback.data.color.name = "color";
    playback.data.color.buffer = color.get_buffer();
    playback.data.color.size = color.get_size();
    playback.data.color.width = color.get_width_pixels();
    playback.data.color.height = color.get_height_pixels();
    playback.data.color.format = "B8G8R8A8_SRGB";
    playback.data.color.timestamp = static_cast<float>(color.get_device_timestamp().count());
    color.reset();

    //Depth
    k4a::image depth = next_capture.get_depth_image();
    playback.data.depth.name = "depth";
    playback.data.depth.buffer = depth.get_buffer();
    playback.data.depth.size = depth.get_size();
    playback.data.depth.width = depth.get_width_pixels();
    playback.data.depth.height = depth.get_height_pixels();
    playback.data.depth.format = "B8G8R8A8_SRGB";
    playback.data.depth.timestamp = static_cast<float>(depth.get_device_timestamp().count());
    depth.reset();

    //IR
    k4a::image ir = next_capture.get_ir_image();
    playback.data.ir.name = "ir";
    playback.data.ir.buffer = ir.get_buffer();
    playback.data.ir.size = ir.get_size();
    playback.data.ir.width = ir.get_width_pixels();
    playback.data.ir.height = ir.get_height_pixels();
    playback.data.ir.timestamp = static_cast<float>(ir.get_device_timestamp().count());
    ir.reset();

    playback.data.data_ready = true;
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
