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

  //Init
  k4a::playback recording = k4a::playback::open(path.c_str());

  this->thread_running = true;
  std::chrono::milliseconds timeout(2000);
  while(thread_running){
    k4a::capture next_capture;
    recording.get_next_capture(&next_capture);

    k4a::image color = next_capture.get_color_image();
    k4a::image depth = next_capture.get_depth_image();
    k4a::image ir    = next_capture.get_ir_image();
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
