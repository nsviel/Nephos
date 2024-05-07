#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n, int index) : k4n::dev::Sensor(node_k4n){
  //---------------------------

  this->param.index = index;
  this->param.name = "capture_" + to_string(index);

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

  //Init elements
  this->param.index = 0;
  this->param.device = k4a::device::open(param.index);
  if(!param.device.is_valid()) return;

  this->param.serial_number = param.device.get_serialnum();
  this->param.version = param.device.get_version();

  //Configuration
  k4n_config->make_sensor_configuration(this);
  k4n_config->make_sensor_color_configuration(this);
  k4n_config->make_capture_calibration(this);
  k4n_config->make_transformation_from_calibration(this);
  this->param.device.start_cameras(&param.configuration);

  //Start capture thread
  this->param.is_capturing = true;

  //---------------------------
}
void Sensor::thread_loop(){
  //---------------------------

  prf::graph::Tasker* tasker = profiler->get_or_create_tasker("capture");
  tasker->loop_begin();

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

  this->param.device.close();
  this->param.is_capturing = false;

  //---------------------------
}

//Subfunction
k4a::capture* Sensor::manage_new_capture(){
  //---------------------------

  k4a::capture* capture = new k4a::capture();
  bool ok = param.device.get_capture(capture, std::chrono::milliseconds(2000));
  if(!capture->is_valid()){
    delete capture;
    return nullptr;
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
    profiler->reset();
    while(is_pause && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}

}
