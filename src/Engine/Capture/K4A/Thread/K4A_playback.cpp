#include "K4A_playback.h"

#include <Engine/Engine.h>
#include <Utility/Function/Timer/FPS_counter.h>
#include <Engine/Capture/K4A/Utils/Namespace.h>


//Constructor / Destructor
K4A_playback::K4A_playback(Engine* engine){
  //---------------------------

  this->fps_counter = new FPS_counter(60);
  this->k4a_data = new eng::kinect::data::Data();
  this->k4a_processing = new K4A_processing(engine);
  this->k4a_config = new eng::kinect::Configuration();

  //---------------------------
}
K4A_playback::~K4A_playback(){
  //---------------------------

  this->stop_thread();
  this->thread.join();

  //---------------------------
}

//Main function
void K4A_playback::start_thread(K4A_device* k4a_device){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&K4A_playback::run_thread, this, k4a_device);
  }

  //---------------------------
}
void K4A_playback::run_thread(K4A_device* k4a_device){
  //---------------------------

  //Get info about file
  this->find_duration(k4a_device);

  //Init playback
  k4a::playback playback = k4a::playback::open(k4a_device->playback.path.c_str());
  if(!playback) return;
  this->thread_running = true;
  k4a_device->player.play = true;
  k4a_device->device.playback = &playback;

  k4a_config->find_file_information(k4a_device);
  k4a_config->make_k4a_configuration(k4a_device);
  k4a_config->init_playback_calibration(k4a_device);
  k4a_config->init_device_transformation(k4a_device);

  //Playback thread
  k4a::capture capture;
  while(thread_running){
    playback.get_next_capture(&capture);
    if(!capture) continue;

    k4a_data->find_data_from_capture(k4a_device, capture);
    k4a_data->find_color_from_depth(k4a_device, capture, k4a_device->device.transformation);

    k4a_processing->convert_into_cloud(k4a_device);

    this->manage_fps(k4a_device->device.fps_mode);
    this->manage_pause(k4a_device);
    this->manage_query_ts(k4a_device);
    this->manage_restart(k4a_device);

    fps_counter->update();
    k4a_device->device.fps = fps_counter->get_fps();
  }

  playback.close();

  //---------------------------
}
void K4A_playback::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

//Subfunction
void K4A_playback::manage_fps(int fps_mode){
  //---------------------------

  switch(fps_mode){
    case K4A_FRAMES_PER_SECOND_5:{
      fps_counter->set_fps_max(5);
    }
    case K4A_FRAMES_PER_SECOND_15:{
      fps_counter->set_fps_max(15);
    }
    case K4A_FRAMES_PER_SECOND_30:{
      fps_counter->set_fps_max(30);
    }
  }

  //---------------------------
}
void K4A_playback::find_duration(K4A_device* k4a_device){
  eng::kinect::structure::Player* player = &k4a_device->player;
  //---------------------------

  k4a::image color;
  k4a::capture capture;
  k4a::playback playback = k4a::playback::open(k4a_device->playback.path.c_str());

  //File duration
  player->duration = playback.get_recording_length().count() / 1000000.0f;

  //File first timestamp
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_BEGIN);
  color = nullptr;
  while(color == nullptr){
    playback.get_next_capture(&capture);
    color = capture.get_color_image();
  }
  player->ts_beg = color.get_device_timestamp().count() / 1000000.0f;

  //File last timestamp
  playback.seek_timestamp(std::chrono::microseconds(0), K4A_PLAYBACK_SEEK_END);
  color = nullptr;
  while(color == nullptr){
    playback.get_previous_capture(&capture);
    color = capture.get_color_image();
  }
  player->ts_end = color.get_device_timestamp().count() / 1000000.0f;

  //---------------------------
}
void K4A_playback::manage_query_ts(K4A_device* k4a_device){
  //---------------------------

  //If a timestamp was querry
  if(k4a_device->player.ts_seek != -1){
    if(k4a_device->player.ts_seek > k4a_device->player.ts_end) k4a_device->player.ts_seek = k4a_device->player.ts_end;
    if(k4a_device->player.ts_seek < k4a_device->player.ts_beg) k4a_device->player.ts_seek = k4a_device->player.ts_beg;
    auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(k4a_device->player.ts_seek));
    k4a_device->device.playback->seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
    k4a_device->player.ts_seek = -1;
  }

  //If a timestamp forawardwas querry
  if(k4a_device->player.ts_forward != 0){
    float ts_forward = k4a_device->player.ts_cur + 5 * k4a_device->player.ts_forward;
    if(ts_forward > k4a_device->player.ts_end) ts_forward = k4a_device->player.ts_end;
    if(ts_forward < k4a_device->player.ts_beg) ts_forward = k4a_device->player.ts_beg;
    auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(ts_forward));
    k4a_device->device.playback->seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
    k4a_device->player.ts_forward = 0;
  }

  //---------------------------
}
void K4A_playback::manage_pause(K4A_device* k4a_device){
  //---------------------------

  //If pause, wait until end pause or end thread
  if(k4a_device->player.pause || !k4a_device->player.play){
    while(k4a_device->player.pause && thread_running && k4a_device->player.ts_seek == -1 && k4a_device->player.ts_forward == 0){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}
void K4A_playback::manage_restart(K4A_device* k4a_device){
  //---------------------------

  if(k4a_device->player.ts_cur == k4a_device->player.ts_end){
    k4a_device->player.play = k4a_device->player.restart;
    k4a_device->player.pause = !k4a_device->player.restart;
    auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(k4a_device->player.ts_beg));
    k4a_device->device.playback->seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
  }

  //---------------------------
}
void K4A_playback::manage_recording(K4A_device* k4a_device, k4a::capture capture){
  //---------------------------

  k4a::record& recorder = k4a_device->recorder.recorder;

  //Start recording
  if(k4a_device->player.record && !recorder.is_valid()){
    recorder = k4a::record::create(k4a_device->recorder.path.c_str(), *k4a_device->device.device, k4a_device->device.k4a_config);
    recorder.write_header();
    k4a_device->recorder.ts_beg = k4a_device->player.ts_cur;
  }

  //Recording
  if(k4a_device->player.record && recorder.is_valid()){
    recorder.write_capture(capture);
    k4a_device->recorder.ts_rec = k4a_device->player.ts_cur - k4a_device->recorder.ts_beg;
  }

  //Flush to file when finish
  if(!k4a_device->player.record && recorder.is_valid()){
    recorder.flush();
    recorder.close();
  }

  //---------------------------
}
