#include "K4A_replay.h"


//Constructor / Destructor
K4A_replay::K4A_replay(){
  //---------------------------

  this->k4a_data = new util::kinect::data::Data();

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
  this->find_file_duration(device->file);

  //Init playback
  k4a::playback playback = k4a::playback::open(device->file.file_path.c_str());
  if(!playback) return;
  this->thread_running = true;
  this->thread_play = true;

  //Playback thread
  k4a::capture capture;
  while(thread_running){
    playback.get_next_capture(&capture);
    if(!capture) break;

    k4a_data->find_data_from_capture(device, capture);
    this->sleep_necessary_time(device->device.fps);

    this->manage_timestamp(&playback);
    this->manage_pause();
    this->manage_restart(&playback, device);
  }

  playback.close();

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
void K4A_replay::sleep_necessary_time(int fps_mode){
  //---------------------------

  switch(fps_mode){
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
void K4A_replay::find_file_duration(util::kinect::structure::Info& info){
  //---------------------------

  k4a::image color;
  k4a::capture capture;
  k4a::playback playback = k4a::playback::open(info.file_path.c_str());

  //File duration
  info.file_duration = playback.get_recording_length().count() / 1000000.0f;

  //File first timestamp
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_BEGIN);
  playback.get_next_capture(&capture);
  color = capture.get_color_image();
  info.ts_beg = color.get_device_timestamp().count() / 1000000.0f;

  //File last timestamp
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_END);
  playback.get_previous_capture(&capture);
  color = capture.get_color_image();
  info.ts_end = color.get_device_timestamp().count() / 1000000.0f;

  //---------------------------
}
void K4A_replay::manage_timestamp(k4a::playback* playback){
  //---------------------------

  if(ts_seek != -1){
    auto ts_seek_ms = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(ts_seek));
    playback->seek_timestamp(ts_seek_ms, K4A_PLAYBACK_SEEK_DEVICE_TIME);
    thread_play = true;
    ts_seek = -1;
  }

  //---------------------------
}
void K4A_replay::manage_pause(){
  //---------------------------

  //If pause, wait until end pause or end thread
  if(thread_pause){
    while(thread_pause && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}
void K4A_replay::manage_restart(k4a::playback* playback, K4A_device* k4a_device){
  //---------------------------

  if(k4a_device->color.image.timestamp == k4a_device->file.ts_end){
    if(thread_restart){
      this->thread_play = true;
      playback->seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_BEGIN);
    }
    else{
      this->thread_play = false;
    }
  }

  //---------------------------
}
