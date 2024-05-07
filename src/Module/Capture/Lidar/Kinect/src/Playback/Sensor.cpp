#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_data = new k4n::processing::Data(node_k4n);
  this->k4n_config = new k4n::utils::Configuration();

  //---------------------------
}
Sensor::~Sensor(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void Sensor::thread_init(){
  k4n::dev::Sensor* k4n_sensor = dynamic_cast<k4n::dev::Sensor*>(sensor);
  //---------------------------

  //Init playback
  if(k4n_sensor->param.path.data == "") return;
  k4n_sensor->param.playback = k4a::playback::open(k4n_sensor->param.path.data.c_str());
  if(!k4n_sensor->param.playback){
    cout<<"[error] Sensor opening problem"<<endl;
    return;
  }

  k4n_config->find_playback_configuration(k4n_sensor);
  k4n_config->find_playback_calibration(k4n_sensor);
  k4n_config->make_transformation_from_calibration(k4n_sensor);

  //---------------------------
}
void Sensor::thread_loop(){
  k4n::dev::Sensor* k4n_sensor = dynamic_cast<k4n::dev::Sensor*>(sensor);
  //---------------------------

  prf::graph::Tasker* tasker = k4n_sensor->profiler->get_or_create_tasker("capture");
  tasker->loop_begin(k4n_sensor->master->operation.fps);

  //Next capture
  tasker->task_begin("capture");
  k4a::capture* capture = manage_new_capture(k4n_sensor);
  if(capture == nullptr) return;
  tasker->task_end("capture");

  //Wait previous threads to finish
  tasker->task_begin("wait");
  this->manage_old_capture(k4n_sensor, capture);
  tasker->task_end("wait");

  //Run processing
  k4n_data->start_thread(k4n_sensor);

  //Loop sleeping
  tasker->task_begin("pause");
  this->manage_pause(k4n_sensor);
  tasker->task_end("pause");

  tasker->loop_end();

  //---------------------------
}
void Sensor::thread_end(){
  k4n::dev::Sensor* k4n_sensor = dynamic_cast<k4n::dev::Sensor*>(sensor);
  //---------------------------

  k4n_sensor->param.playback.close();

  //---------------------------
}

//Subfunction
k4a::capture* Sensor::manage_new_capture(k4n::dev::Sensor* sensor){
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
void Sensor::manage_old_capture(k4n::dev::Sensor* sensor, k4a::capture* capture){
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
void Sensor::manage_pause(k4n::dev::Sensor* sensor){
  //---------------------------

  //If pause, wait until end pause or end thread
  bool& is_play = sensor->master->player->get_state_play();
  bool& is_pause = sensor->master->player->get_state_pause();
  if(is_pause || !is_play){
    //Clear thread profiler and wait subthread fulfillment
    sensor->profiler->reset();
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
void Sensor::manage_restart(k4n::dev::Sensor* sensor){
  //---------------------------

  float& ts_end = sensor->master->player->get_ts_end();
  if(sensor->color.data.timestamp == ts_end){
    sensor->master->manage_restart();
    //sensor->master->player->play = true;
    //sensor->master->player->pause = false;
  }

  //---------------------------
}

}
