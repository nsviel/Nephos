#include "K4A_replay.h"

#include <UTL_capture/UTL_kinect/K4A_struct/Struct_k4a_swarm.h>
#include <UTL_capture/UTL_kinect/K4A_device/K4A_device.h>
#include <UTL_capture/UTL_kinect/K4A_data/K4A_data.h>


//Constructor / Destructor
K4A_replay::K4A_replay(){
  //---------------------------

  this->k4a_data = new K4A_data();

  //---------------------------
}
K4A_replay::~K4A_replay(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void K4A_replay::start_thread(K4A_device* device){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&K4A_replay::run_capture, this, device);
  }

  //---------------------------
}

//Subfunction
void K4A_replay::run_capture(K4A_device* device){
  //---------------------------

  k4a::capture next_capture;
  this->thread_running = true;
  while(thread_running){
    k4a::playback playback = k4a::playback::open(device->info.file_path.c_str());
    if (!playback) {
      cout<<"[error] Failed to open playback file"<<endl;
      return;
    }

    //Read entire video
    while(playback.get_next_capture(&next_capture)){
      if (!next_capture) {
        cout<<"[error] Failed to get next capture"<<endl;
        break;
      }

      k4a_data->find_data_from_capture(&device->data, next_capture);
      this->sleep_necessary_time(device);
    }

    playback.close();
  }

  //---------------------------
}
void K4A_replay::sleep_necessary_time(K4A_device* device){
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
