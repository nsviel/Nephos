#include "Capture.h"

#include <K4N/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::thread{

//Constructor / Destructor
Capture::Capture(k4n::Node* node_k4n){
  //---------------------------

  this->k4a_data = new k4n::processing::Data(node_k4n);
  this->k4n_config = new k4n::config::Configuration();
  this->k4n_calibration = new k4n::config::Calibration();

  //---------------------------
}
Capture::~Capture(){
  //---------------------------

  this->stop_thread();

  //---------------------------
}

//Main function
void Capture::start_thread(k4n::dev::Sensor* sensor){
  if(sensor == nullptr) return;
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Capture::run_thread, this, sensor);
  }

  //---------------------------
  this->thread_running = true;
  this->thread_idle = false;
}
void Capture::run_thread(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("capture");
  k4n::dev::Master* master = sensor->master;
  //---------------------------

  //Init elements
  sensor->param.index = 0;
  sensor->param.device = k4a::device::open(sensor->param.index);
  if(!sensor->param.device.is_valid()) return;

  sensor->param.serial_number = sensor->param.device.get_serialnum();
  sensor->param.version = sensor->param.device.get_version();

  //Configuration
  k4n_config->make_sensor_configuration(sensor);
  k4n_config->make_sensor_color_configuration(sensor);
  k4n_calibration->make_capture_calibration(sensor);
  k4n_calibration->make_transformation_from_calibration(sensor);
  sensor->param.device.start_cameras(&sensor->param.configuration);

  //Start capture thread
  sensor->param.is_capturing = true;
  while(thread_running){
    //Next capture
    tasker->loop_begin();
    k4a::capture* capture = manage_new_capture(sensor);
    this->manage_old_capture(sensor, capture);

    //Find data from capture
    k4a_data->start_thread(sensor);

    //Manage event
    this->manage_pause(sensor);
    tasker->loop_end();
  }

  sensor->param.device.close();
  sensor->param.is_capturing = false;

  //---------------------------
  this->thread_idle = true;
}
void Capture::stop_thread(){
  //---------------------------

  this->thread_running = false;
  this->wait_thread();
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------

}
void Capture::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
k4a::capture* Capture::manage_new_capture(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("capture");
  //---------------------------

  tasker->task_begin("capture");

  k4a::capture* capture = new k4a::capture();
  bool ok = sensor->param.device.get_capture(capture, std::chrono::milliseconds(2000));
  if(!capture->is_valid()){
    delete capture;
    return nullptr;
  }

  tasker->task_end("capture");

  //---------------------------
  return capture;
}
void Capture::manage_old_capture(k4n::dev::Sensor* sensor, k4a::capture* capture){
  if(capture == nullptr) return;
  static k4a::capture* capture_old = nullptr;
  //---------------------------

  delete capture_old;
  capture_old = capture;
  sensor->param.capture = capture;

  //---------------------------
}
void Capture::manage_pause(k4n::dev::Sensor* sensor){
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

}
