#include "K4A_playback.h"

#include <Engine/Engine.h>
#include <Utility/Function/Timer/FPS_counter.h>
#include <Utility/Function/Timer/FPS_control.h>
#include <Engine/Capture/K4N/Utils/Namespace.h>


//Constructor / Destructor
K4A_playback::K4A_playback(Engine* engine){
  //---------------------------

  this->fps_counter = new FPS_counter();
  this->fps_control = new FPS_control(30);

  this->k4a_data = new k4n::data::Data();
  this->k4a_processing = new k4n::data::Cloud(engine);
  this->k4n_configuration = new k4n::config::Configuration();
  this->k4n_calibration = new k4n::config::Calibration();
  this->k4n_operation= new k4n::utils::Operation();

  //---------------------------
}
K4A_playback::~K4A_playback(){
  //---------------------------

  this->stop_thread();
  this->thread.join();

  //---------------------------
}

//Main function
void K4A_playback::start_thread(k4n::dev::Sensor* k4n_sensor){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&K4A_playback::run_thread, this, k4n_sensor);
  }

  //---------------------------
}
void K4A_playback::run_thread(k4n::dev::Sensor* k4n_sensor){
  //---------------------------

  //Init playback
  k4a::playback playback = k4a::playback::open(k4n_sensor->param.file_path.c_str());
  if(!playback) return;
  this->thread_running = true;
  k4n_sensor->player.play = true;
  k4n_sensor->param.playback = &playback;

  k4n_configuration->find_playback_configuration(k4n_sensor);
  k4n_configuration->make_device_configuration(k4n_sensor);
  k4n_calibration->find_playback_calibration(k4n_sensor);
  k4n_calibration->make_device_transformation(k4n_sensor);

  //Playback thread
  k4a::capture capture;
  while(thread_running){
    fps_control->start();

    this->manage_pause(k4n_sensor);
    this->manage_query_ts(k4n_sensor);
    this->manage_restart(k4n_sensor);

    playback.get_next_capture(&capture);
    if(!capture) continue;

    k4a_data->find_data_from_capture(k4n_sensor, capture);
    k4a_data->find_color_from_depth(k4n_sensor, capture, k4n_sensor->param.transformation);

    k4a_processing->convert_into_cloud(k4n_sensor);

    fps_control->stop();
    fps_control->set_fps_max(k4n_sensor->param.fps.query);
    k4n_sensor->param.fps.current = fps_counter->update();
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
void K4A_playback::manage_query_ts(k4n::dev::Sensor* k4n_sensor){
  //---------------------------

  //If a timestamp was querry
  if(k4n_sensor->player.ts_seek != -1){
    if(k4n_sensor->player.ts_seek > k4n_sensor->player.ts_end) k4n_sensor->player.ts_seek = k4n_sensor->player.ts_end;
    if(k4n_sensor->player.ts_seek < k4n_sensor->player.ts_beg) k4n_sensor->player.ts_seek = k4n_sensor->player.ts_beg;
    auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(k4n_sensor->player.ts_seek));
    k4n_sensor->param.playback->seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
    k4n_sensor->player.ts_seek = -1;
  }

  //If a timestamp forawardwas querry
  if(k4n_sensor->player.ts_forward != 0){
    float ts_forward = k4n_sensor->player.ts_cur + 5 * k4n_sensor->player.ts_forward;
    if(ts_forward > k4n_sensor->player.ts_end) ts_forward = k4n_sensor->player.ts_end;
    if(ts_forward < k4n_sensor->player.ts_beg) ts_forward = k4n_sensor->player.ts_beg;
    auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(ts_forward));
    k4n_sensor->param.playback->seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
    k4n_sensor->player.ts_forward = 0;
  }

  //---------------------------
}
void K4A_playback::manage_pause(k4n::dev::Sensor* k4n_sensor){
  //---------------------------

  //If pause, wait until end pause or end thread
  if(k4n_sensor->player.pause || !k4n_sensor->player.play){
    while(k4n_sensor->player.pause && thread_running && k4n_sensor->player.ts_seek == -1 && k4n_sensor->player.ts_forward == 0){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}
void K4A_playback::manage_restart(k4n::dev::Sensor* k4n_sensor){
  //---------------------------

  if(k4n_sensor->player.ts_cur == k4n_sensor->player.ts_end){
    k4n_sensor->player.play = k4n_sensor->player.restart;
    k4n_sensor->player.pause = !k4n_sensor->player.restart;
    auto ts_querry = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(k4n_sensor->player.ts_beg));
    k4n_sensor->param.playback->seek_timestamp(ts_querry, K4A_PLAYBACK_SEEK_DEVICE_TIME);
  }

  //---------------------------
}
void K4A_playback::manage_recording(k4n::dev::Sensor* k4n_sensor, k4a::capture capture){
  //---------------------------

  k4a::record& recorder = k4n_sensor->recorder.recorder;

  //Start recording
  if(k4n_sensor->player.record && !recorder.is_valid()){
    recorder = k4a::record::create(k4n_sensor->recorder.path.c_str(), *k4n_sensor->param.device, k4n_sensor->param.configuration);
    recorder.write_header();
    k4n_sensor->recorder.ts_beg = k4n_sensor->player.ts_cur;
  }

  //Recording
  if(k4n_sensor->player.record && recorder.is_valid()){
    recorder.write_capture(capture);
    k4n_sensor->recorder.ts_rec = k4n_sensor->player.ts_cur - k4n_sensor->recorder.ts_beg;
  }

  //Flush to file when finish
  if(!k4n_sensor->player.record && recorder.is_valid()){
    recorder.flush();
    recorder.close();
  }

  //---------------------------
}
