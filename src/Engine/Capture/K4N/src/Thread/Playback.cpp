#include "Playback.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>


namespace eng::k4n::thread{

//Constructor / Destructor
Playback::Playback(eng::k4n::Node* k4n_node){
  //---------------------------

  this->fps_counter = new FPS_counter();
  this->fps_control = new FPS_control(30);

  this->k4a_data = new eng::k4n::data::Data();
  this->k4a_cloud = new eng::k4n::data::Cloud(k4n_node);
  this->k4n_configuration = new eng::k4n::config::Configuration();
  this->k4n_calibration = new eng::k4n::config::Calibration();
  this->k4n_operation= new eng::k4n::utils::Operation();

  //---------------------------
}
Playback::~Playback(){
  //---------------------------

  this->stop_thread();
  this->thread.join();

  //---------------------------
}

//Main function
void Playback::start_thread(eng::k4n::dev::Sensor* sensor){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Playback::run_thread, this, sensor);
  }

  //---------------------------
}
void Playback::run_thread(eng::k4n::dev::Sensor* sensor){
  //---------------------------

  //Init playback
  k4a::playback playback = k4a::playback::open(sensor->param.path_data.c_str());
  if(!playback) return;
  this->thread_running = true;
  sensor->param.playback = &playback;

  k4n_configuration->find_playback_configuration(sensor);
  k4n_configuration->make_device_configuration(sensor);
  k4n_calibration->find_playback_calibration(sensor);
  k4n_calibration->make_device_transformation(sensor);

  //Playback thread
  k4a::capture capture;
  while(thread_running){
    fps_control->start();

    playback.get_next_capture(&capture);
    if(!capture) continue;

    k4a_data->find_data_from_capture(sensor, capture);
    k4a_data->find_color_from_depth(sensor, capture, sensor->param.transformation);

    k4a_cloud->convert_into_cloud(sensor);
    this->manage_pause(sensor);
    this->manage_restart(sensor);

    fps_control->stop();
    fps_control->set_fps_max(sensor->param.fps.query);
    sensor->param.fps.current = fps_counter->update();
  }

  playback.close();

  //---------------------------
}
void Playback::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}

//Subfunction
void Playback::manage_pause(eng::k4n::dev::Sensor* sensor){
  //---------------------------

  //If pause, wait until end pause or end thread
  bool& is_paused = sensor->master->player.pause;
  if(is_paused || !sensor->master->player.play){
    while(is_paused && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}
void Playback::manage_restart(eng::k4n::dev::Sensor* sensor){
  //---------------------------

  if(sensor->color.image.timestamp >= sensor->master->player.ts_end){
    sensor->master->manage_restart();
  }

  //---------------------------
}
void Playback::manage_recording(eng::k4n::dev::Sensor* sensor, k4a::capture capture){
  //---------------------------
/*
  k4a::record& recorder = sensor->recorder.recorder;

  //Start recording
  if(sensor->player.record && !recorder.is_valid()){
    recorder = k4a::record::create(sensor->recorder.path.c_str(), *sensor->param.device, sensor->param.configuration);
    recorder.write_header();
    sensor->recorder.ts_beg = sensor->color.image.timestamp;
  }

  //Recording
  if(sensor->player.record && recorder.is_valid()){
    recorder.write_capture(capture);
    sensor->recorder.ts_rec = sensor->color.image.timestamp - sensor->recorder.ts_beg;
  }

  //Flush to file when finish
  if(!sensor->player.record && recorder.is_valid()){
    recorder.flush();
    recorder.close();
  }
*/
  //---------------------------
}


}
