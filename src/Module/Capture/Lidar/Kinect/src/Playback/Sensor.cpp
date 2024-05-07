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
  this->playback.handle = k4a::playback::open(param.path.data.c_str());
  if(!playback.handle){
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

  this->playback.handle.close();

  //---------------------------
}

//Subfunction
k4a::capture* Sensor::manage_new_capture(){
  //---------------------------

  k4a::capture* capture = new k4a::capture();
  bool capture_left = playback.handle.get_next_capture(capture);
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
  bool& is_play = master->get_state_play();
  bool& is_pause = master->get_state_pause();
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

  float& ts_end = master->get_ts_end();
  float& ts_beg = master->get_ts_beg();
  if(color.data.timestamp == ts_end){
    this->manage_ts_query(ts_beg);
  }

  //---------------------------
}
void Sensor::manage_reset(){
  //---------------------------

  float& ts_beg = master->get_ts_beg();
  this->manage_ts_query(ts_beg);

  //---------------------------
}
void Sensor::manage_ts_query(float ts_querry){
  //---------------------------

  auto ts = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(ts_querry));
  playback.handle.seek_timestamp(ts, K4A_PLAYBACK_SEEK_DEVICE_TIME);

  //---------------------------
}


}
