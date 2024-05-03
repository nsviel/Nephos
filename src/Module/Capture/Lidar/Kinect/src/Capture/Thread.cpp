#include "Thread.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Thread::Thread(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_data = new k4n::processing::Data(node_k4n);
  this->k4n_config = new k4n::utils::Configuration();

  //---------------------------
}
Thread::~Thread(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void Thread::thread_init(dat::base::Sensor* sensor){
  k4n::dev::Sensor* k4n_sensor = dynamic_cast<k4n::dev::Sensor*>(sensor);
  //---------------------------

  //Init elements
  k4n_sensor->param.index = 0;
  k4n_sensor->param.device = k4a::device::open(k4n_sensor->param.index);
  if(!k4n_sensor->param.device.is_valid()) return;

  k4n_sensor->param.serial_number = k4n_sensor->param.device.get_serialnum();
  k4n_sensor->param.version = k4n_sensor->param.device.get_version();

  //Configuration
  k4n_config->make_sensor_configuration(k4n_sensor);
  k4n_config->make_sensor_color_configuration(k4n_sensor);
  k4n_config->make_capture_calibration(k4n_sensor);
  k4n_config->make_transformation_from_calibration(k4n_sensor);
  k4n_sensor->param.device.start_cameras(&k4n_sensor->param.configuration);

  //Start capture thread
  k4n_sensor->param.is_capturing = true;

  //---------------------------
}
void Thread::thread_loop(dat::base::Sensor* sensor){
  k4n::dev::Sensor* k4n_sensor = dynamic_cast<k4n::dev::Sensor*>(sensor);
  //---------------------------

  prf::graph::Tasker* tasker = k4n_sensor->profiler->get_or_create_tasker("capture");
  tasker->loop_begin();

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
void Thread::thread_end(dat::base::Sensor* sensor){
  k4n::dev::Sensor* k4n_sensor = dynamic_cast<k4n::dev::Sensor*>(sensor);
  //---------------------------

  k4n_sensor->param.device.close();
  k4n_sensor->param.is_capturing = false;

  //---------------------------
}

//Subfunction
k4a::capture* Thread::manage_new_capture(k4n::dev::Sensor* sensor){
  //---------------------------

  k4a::capture* capture = new k4a::capture();
  bool ok = sensor->param.device.get_capture(capture, std::chrono::milliseconds(2000));
  if(!capture->is_valid()){
    delete capture;
    return nullptr;
  }

  //---------------------------
  return capture;
}
void Thread::manage_old_capture(k4n::dev::Sensor* sensor, k4a::capture* capture){
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
void Thread::manage_pause(k4n::dev::Sensor* sensor){
  //---------------------------

  //If pause, wait until end pause or end thread
  bool& is_play = sensor->master->player->get_state_play();
  bool& is_pause = sensor->master->player->get_state_pause();
  if(is_pause || !is_play){
    sensor->profiler->reset();
    while(is_pause && thread_running){
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
  }

  //---------------------------
}

}
