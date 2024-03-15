#include "Capture.h"

#include <K4N/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::thread{

//Constructor / Destructor
Capture::Capture(k4n::structure::Struct_k4n* struct_k4n){
  //---------------------------

  this->k4a_data = new k4n::processing::Data(struct_k4n);
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
    k4a::capture* capture = manage_capture(sensor);
    this->manage_capture_endlife(capture);
    if(capture == nullptr){
      continue;
    }

    //Find data from capture
    k4a_data->start_thread(sensor, capture);

    //Manage event
    this->manage_recording(sensor, capture);
    this->manage_pause(sensor);
    tasker->loop_end();
  }

  sensor->param.device.close();
  sensor->param.is_capturing = false;

  //---------------------------

}
void Capture::stop_thread(){
  //---------------------------

  this->thread_running = false;
  this->wait_thread();
  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
  this->thread_idle = true;
}
void Capture::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  k4a_data->wait_thread();

  //---------------------------
}

//Subfunction
k4a::capture* Capture::manage_capture(k4n::dev::Sensor* sensor){
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
void Capture::manage_recording(k4n::dev::Sensor* sensor, k4a::capture* capture){
  k4a::record& recorder = sensor->recorder.handle;
  k4n::dev::Master* master = sensor->master;
  //---------------------------

  if(master->recorder.mode != k4n::recorder::MKV) return;

  //Start recording
  if(master->player.record && !recorder.is_valid()){
    //Check if directory exists, if not create it
    string path_dir = sensor->master->recorder.folder;
    if(!directory::is_dir_exist(path_dir)){
      directory::create_new(path_dir);
    }

    //Create recorder and file, and write header
    string path = path_dir + "/" + sensor->name + ".mkv";
    recorder = k4a::record::create(path.c_str(), sensor->param.device, sensor->param.configuration);
    recorder.write_header();

    //Set sensor info
    sensor->recorder.folder = master->recorder.folder;
    sensor->recorder.ts_beg = sensor->master->player.ts_cur;
  }
  //Recording
  else if(master->player.record && recorder.is_valid()){
    recorder.write_capture(*capture);
    sensor->recorder.ts_rec = sensor->master->player.ts_cur - sensor->recorder.ts_beg;
  }
  //Flush to file when finish
  else if(!master->player.record && recorder.is_valid()){
    recorder.flush();
    recorder.close();
  }

  //---------------------------
}
void Capture::manage_capture_endlife(k4a::capture* capture){
  static k4a::capture* capture_old = nullptr;
  //---------------------------

  k4a_data->wait_thread();
  delete capture_old;
  capture_old = capture;

  //---------------------------
}

}
