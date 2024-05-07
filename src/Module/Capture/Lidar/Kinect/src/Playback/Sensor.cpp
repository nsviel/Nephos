#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n, string path) : k4n::dev::Sensor(node_k4n){
  //---------------------------

  this->param.path.data = path;
  this->param.name = utl::path::get_name_from_path(path);

  //---------------------------
}
Sensor::~Sensor(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void Sensor::thread_init(){
  //---------------------------

  //Init playback
  if(param.path.data == "") return;
  this->param.playback = k4a::playback::open(param.path.data.c_str());
  if(!param.playback){
    cout<<"[error] Sensor opening problem"<<endl;
    return;
  }

  k4n_config->find_playback_configuration(this);
  k4n_config->find_playback_calibration(this);
  k4n_config->make_transformation_from_calibration(this);

  //---------------------------
}
void Sensor::thread_loop(){
  //---------------------------

  prf::graph::Tasker* tasker = profiler->get_or_create_tasker("capture");
  tasker->loop_begin(master->operation.fps);

  //Next capture
  tasker->task_begin("capture");
  k4a::capture* capture = manage_new_capture();
  if(capture == nullptr) return;
  tasker->task_end("capture");

  //Wait previous threads to finish
  tasker->task_begin("wait");
  this->manage_old_capture(capture);
  tasker->task_end("wait");

  //Run processing
  k4n_data->start_thread(this);

  //Loop sleeping
  tasker->task_begin("pause");
  this->manage_pause();
  tasker->task_end("pause");

  tasker->loop_end();

  //---------------------------
}
void Sensor::thread_end(){
  //---------------------------

  this->param.playback.close();

  //---------------------------
}

//Subfunction
k4a::capture* Sensor::manage_new_capture(){
  //---------------------------

  k4a::capture* capture = new k4a::capture();
  bool capture_left = param.playback.get_next_capture(capture);
  if(capture_left == false){
    capture = nullptr;
    this->manage_restart();
  }

  //---------------------------
  return capture;
}
void Sensor::manage_old_capture(k4a::capture* capture){
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
  this->param.capture = capture;

  //---------------------------
}
void Sensor::manage_pause(){
  //---------------------------

  //If pause, wait until end pause or end thread
  bool& is_play = master->player->get_state_play();
  bool& is_pause = master->player->get_state_pause();
  if(is_pause || !is_play){
    //Clear thread profiler and wait subthread fulfillment
    this->profiler->reset();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    //Pause loop
    this->thread_paused = true;
    while(is_pause && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    this->thread_paused = false;
  }

  //---------------------------
}
void Sensor::manage_restart(){
  //---------------------------

  float& ts_end = master->player->get_ts_end();
  if(color.data.timestamp == ts_end){
    master->manage_restart();
    //sensor->master->player->play = true;
    //sensor->master->player->pause = false;
  }

  //---------------------------
}

}
