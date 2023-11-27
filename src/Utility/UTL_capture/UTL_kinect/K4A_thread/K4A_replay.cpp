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
    this->thread = std::thread(&K4A_replay::run_thread, this, device);
  }

  //---------------------------
}
void K4A_replay::run_thread(K4A_device* device){
  //---------------------------

  //Get info about file
  this->find_file_info(device);

  //Playback thread
  k4a::capture next_capture;
  this->thread_running = true;
  while(thread_running){
    //Open file for playback
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

      if(ts_seek != -1){
        auto ts_seek_ms = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(ts_seek));
        playback.seek_timestamp(ts_seek_ms, K4A_PLAYBACK_SEEK_DEVICE_TIME);
        ts_seek = -1;
      }

      this->manage_current_timestamp(device, next_capture);
      k4a_data->find_data_from_capture(&device->data, next_capture);
      this->sleep_necessary_time(device);
      this->manage_thread_pause();
    }

    playback.close();
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

//Subfunction
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
void K4A_replay::find_file_info(K4A_device* device){
  //---------------------------

  k4a::image color;
  k4a::capture capture;
  k4a::playback playback = k4a::playback::open(device->info.file_path.c_str());

  //File duration
  device->info.file_duration = playback.get_recording_length();

  //File first timestamp
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_BEGIN);
  playback.get_next_capture(&capture);
  color = capture.get_color_image();
  device->info.ts_beg = color.get_device_timestamp();

  //File last timestamp
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_END);
  playback.get_previous_capture(&capture);
  color = capture.get_color_image();
  device->info.ts_end = color.get_device_timestamp();

  //---------------------------
}
void K4A_replay::manage_current_timestamp(K4A_device* device, k4a::capture capture){
  //---------------------------

  k4a::image color = capture.get_color_image();
  device->info.ts_cur = color.get_device_timestamp();




  //---------------------------
}
void K4A_replay::manage_thread_pause(){
  //---------------------------

  //If pause, wait until end pause or end thread
  if(thread_pause){
    while(thread_pause && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}
