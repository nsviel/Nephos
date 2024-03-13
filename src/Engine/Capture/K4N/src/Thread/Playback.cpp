#include "Playback.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::thread{

//Constructor / Destructor
Playback::Playback(k4n::structure::Struct_k4n* struct_k4n){
  //---------------------------

  this->k4a_data = new k4n::processing::Data(struct_k4n);
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
  this->thread_running = true;
  this->thread_idle = false;
}
void Playback::run_thread(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_tasker("capture");
  k4n::dev::Master* master = sensor->master;
  //---------------------------

  //Init playback
  if(sensor->param.path.data == "") return;
  sensor->param.playback = k4a::playback::open(sensor->param.path.data.c_str());
  if(!sensor->param.playback) return;

  k4n_configuration->find_playback_configuration(sensor);
  k4n_calibration->find_playback_calibration(sensor);
  k4n_calibration->make_transformation_from_calibration(sensor);

  //Playback thread
  while(thread_running){
    //Next capture
    tasker->loop_begin(master->operation.fps);
    k4a::capture* capture = manage_capture(sensor);
    this->manage_capture_endlife(capture);
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
}
void Playback::stop_thread(){
  //---------------------------

  this->thread_running = false;
  this->wait_thread();

  //---------------------------
  this->thread_idle = true;
}
void Playback::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  if(thread.joinable()){
    thread.join();
  }
  k4a_data->wait_thread();

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
    //Clear thread profiler and wait subthread fulfillment
    sensor->profiler->clear();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    k4a_data->wait_thread();

    //Pause loop
    this->thread_paused = true;
    while(is_paused && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    this->thread_paused = false;
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
void Playback::manage_capture_endlife(k4a::capture* capture){
  static k4a::capture* capture_old = nullptr;
  //---------------------------

  k4a_data->wait_thread();
  delete capture_old;
  capture_old = capture;

  //---------------------------
}


}
