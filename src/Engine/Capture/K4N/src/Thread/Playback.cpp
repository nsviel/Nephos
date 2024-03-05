#include "Playback.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::thread{

//Constructor / Destructor
Playback::Playback(){
  //---------------------------

  this->k4a_data = new k4n::data::Data();
  this->k4n_configuration = new k4n::config::Configuration();
  this->k4n_calibration = new k4n::config::Calibration();
  this->k4n_operation= new k4n::utils::Operation();

  //---------------------------
}
Playback::~Playback(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void Playback::start_thread(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  if(sensor->param.path.data == "") return;
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Playback::run_thread, this, sensor);
  }

  //---------------------------
}
void Playback::run_thread(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_tasker("capture");
  k4n::dev::Master* master = sensor->master;
  //---------------------------

  //Init playback
  this->thread_running = true;
  this->thread_idle = false;
  if(sensor->param.path.data == "") return;
  sensor->param.playback = k4a::playback::open(sensor->param.path.data.c_str());
  if(!sensor->param.playback) return;

  k4n_configuration->find_playback_configuration(sensor);
  k4n_calibration->find_playback_calibration(sensor);
  k4n_configuration->make_device_configuration(sensor);
  k4n_calibration->make_device_transformation(sensor);

  //Playback thread
  while(thread_running){
    //Next capture
    tasker->loop_begin(master->operation.fps);
    k4a::capture* capture = manage_capture(sensor);
    if(!capture->is_valid()) continue;

    //Find data from capture
    k4a_data->start_thread(sensor, capture);

    //Manage event
    this->manage_pause(sensor);
    this->manage_restart(sensor);
    tasker->loop_end();
  }

  sensor->param.playback.close();

  //---------------------------
  this->thread_idle = true;
}
void Playback::stop_thread(){
  //---------------------------

  this->thread_running = false;
  this->wait_thread_idle();
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
}
void Playback::wait_thread_idle(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  k4a_data->wait_thread_idle();

  //---------------------------
}

//Subfunction
k4a::capture* Playback::manage_capture(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_tasker("capture");
  k4n::dev::Master* master = sensor->master;
  //---------------------------

  tasker->task_begin("capture");

  k4a::capture* capture = new k4a::capture();
  bool ok = sensor->param.playback.get_next_capture(capture);
  if(!ok) sensor->master->manage_restart();

  tasker->task_end("capture");

  //---------------------------
  return capture;
}
void Playback::manage_pause(k4n::dev::Sensor* sensor){
  //---------------------------

  //If pause, wait until end pause or end thread
  bool& is_paused = sensor->master->player.pause;
  if(is_paused || !sensor->master->player.play){
    sensor->profiler->clear();
    while(is_paused && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}
void Playback::manage_restart(k4n::dev::Sensor* sensor){
  //---------------------------

  if(sensor->color.data.timestamp >= sensor->master->player.ts_end){
    sensor->master->manage_restart();
  }

  //---------------------------
}
void Playback::manage_recording(k4n::dev::Sensor* sensor, k4a::capture capture){
  //---------------------------
/*
  k4a::record& recorder = sensor->recorder.recorder;

  //Start recording
  if(sensor->player.record && !recorder.is_valid()){
    recorder = k4a::record::create(sensor->recorder.path.c_str(), *sensor->param.device, sensor->param.configuration);
    recorder.write_header();
    sensor->recorder.ts_beg = sensor->color.data.timestamp;
  }

  //Recording
  if(sensor->player.record && recorder.is_valid()){
    recorder.write_capture(capture);
    sensor->recorder.ts_rec = sensor->color.data.timestamp - sensor->recorder.ts_beg;
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
