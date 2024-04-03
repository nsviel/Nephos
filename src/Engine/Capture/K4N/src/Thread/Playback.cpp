#include "Playback.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::thread{

//Constructor / Destructor
Playback::Playback(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_data = new k4n::processing::Data(node_k4n);
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
  prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("capture");
  k4n::dev::Master* master = sensor->master;
  //---------------------------

  //Init playback
  if(sensor->param.path.data == "") return;
  sensor->param.playback = k4a::playback::open(sensor->param.path.data.c_str());
  if(!sensor->param.playback){
    cout<<"[error] Playback opening problem"<<endl;
    return;
  }

  k4n_configuration->find_playback_configuration(sensor);
  k4n_calibration->find_playback_calibration(sensor);
  k4n_calibration->make_transformation_from_calibration(sensor);

  //Playback thread
  while(thread_running){
    tasker->loop_begin(master->operation.fps);

    //Next capture
    tasker->task_begin("capture");
    k4a::capture* capture = manage_new_capture(sensor);
    if(capture == nullptr) continue;
    tasker->task_end("capture");

    //Wait previous threads to finish
    tasker->task_begin("wait");
    this->manage_old_capture(sensor, capture);
    tasker->task_end("wait");

    //Run processing
    k4n_data->start_thread(sensor);

    //Loop sleeping
    tasker->task_begin("pause");
    this->manage_pause(sensor);
    tasker->task_end("pause");

    tasker->loop_end();
  }

  sensor->param.playback.close();

  //---------------------------
  this->thread_idle = true;
}
void Playback::stop_thread(){
  //---------------------------

  this->thread_running = false;
  if(thread.joinable()){
    thread.join();
  }
  k4n_data->wait_thread();

  //---------------------------
}
void Playback::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_paused == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  k4n_data->wait_thread();

  //---------------------------
}

//Subfunction
k4a::capture* Playback::manage_new_capture(k4n::dev::Sensor* sensor){
  //---------------------------

  k4a::capture* capture = new k4a::capture();
  bool capture_left = sensor->param.playback.get_next_capture(capture);
  if(capture_left == false){
    capture = nullptr;
    this->manage_restart(sensor);
  }

  //---------------------------
  return capture;
}
void Playback::manage_old_capture(k4n::dev::Sensor* sensor, k4a::capture* capture){
  static std::queue<k4a::capture*> capture_queue;
  //---------------------------

  // Add the new capture to the queue
  capture_queue.push(capture);

  // Check if the queue size exceeds 5
  k4n_data->wait_thread();
  if(capture_queue.size() > 5){
    // Delete the oldest capture
    delete capture_queue.front();
    capture_queue.pop();
  }

  // Update the sensor parameter
  sensor->param.capture = capture;

  //---------------------------
}
void Playback::manage_pause(k4n::dev::Sensor* sensor){
  //---------------------------

  //If pause, wait until end pause or end thread
  bool& is_paused = sensor->master->player.pause;
  if(is_paused || !sensor->master->player.play){
    //Clear thread profiler and wait subthread fulfillment
    sensor->profiler->reset();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

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

  if(sensor->color.data.timestamp == sensor->master->player.ts_end){
    sensor->master->manage_restart();
    sensor->master->player.play = true;
    sensor->master->player.pause = false;
  }

  //---------------------------
}



}
