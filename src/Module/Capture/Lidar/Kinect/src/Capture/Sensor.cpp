#include "Sensor.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n, int index) : k4n::dev::Sensor(node_k4n){
  //---------------------------

  this->device.index = index;
  this->name = "capture_" + to_string(index);

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
  this->device.index = 0;
  this->device.handle = k4a::device::open(device.index);
  if(!device.handle.is_valid()) return;

  this->device.serial_number = device.handle.get_serialnum();
  this->device.version = device.handle.get_version();

  //Configuration
  k4n_config->make_sensor_configuration(this);
  k4n_config->make_sensor_color_configuration(this);
  k4n_config->make_capture_calibration(this);
  k4n_config->make_transformation_from_calibration(this);
  this->device.handle.start_cameras(&device.configuration);

  //Start capture thread
  this->device.is_capturing = true;

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

  this->device.handle.close();
  this->device.is_capturing = false;

  //---------------------------
}

//Subfunction
k4a::capture* Sensor::manage_new_capture(){
  //---------------------------

  k4a::capture* capture = new k4a::capture();
  bool ok = device.handle.get_capture(capture, std::chrono::milliseconds(2000));
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
  this->device.capture = capture;

  //---------------------------
}
void Sensor::manage_pause(){
  //---------------------------

  //If pause, wait until end pause or end thread
  bool& is_play = master->get_state_play();
  bool& is_pause = master->get_state_pause();
  if(is_pause || !is_play){
    profiler->reset();
    while(is_pause && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}
void Sensor::manage_reset(){
  //---------------------------

  this->reset();
  this->run_thread();

  //---------------------------
}

}
