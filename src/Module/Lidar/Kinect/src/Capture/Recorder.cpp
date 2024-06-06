#include "Recorder.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Recorder::Recorder(){
  //---------------------------

  this->format = "mkv";

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::start_thread(k4n::structure::Sensor* sensor, std::string path){
  //---------------------------

  if(!thread_running){
    this->thread_running = true;
    this->thread = std::thread(&Recorder::run_thread, this, sensor, path);
  }

  //---------------------------
}
void Recorder::run_thread(k4n::structure::Sensor* sensor, std::string path){
  //---------------------------

  this->export_start(sensor, path);
  this->export_loop(sensor);
  this->export_stop(sensor);

  //---------------------------
  this->thread_running = false;
}
void Recorder::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(thread_running){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Recorder::export_start(k4n::structure::Sensor* sensor, std::string path){
  //---------------------------

  //Recorder
  k4a::record& recorder = sensor->device.recorder;
  if(recorder.is_valid()) return;

  //Check if directory exists, if not create it
  std::string path_dir = utl::path::get_dir_from_path(path);
  if(!utl::directory::is_exist(path_dir)){
    utl::directory::create(path_dir);
  }

  //Create recorder and file, and write header
  recorder = k4a::record::create(path.c_str(), sensor->device.handle, sensor->device.configuration);
  recorder.write_header();

  //Set info
  //master->recorder.path = path;
  //master->recorder.file_size = 0;
  //master->recorder.ts_beg = sensor->set_parent->ts_cur;

  //---------------------------
}
void Recorder::export_loop(k4n::structure::Sensor* sensor){
  //---------------------------

  //Recorder
  k4a::record& recorder = sensor->device.recorder;
  if(!recorder.is_valid()) return;

  //Record capture
  k4a::capture* capture = sensor->device.capture;
  recorder.write_capture(*capture);

  //master->recorder.ts_rec = sensor->set_parent->ts_cur - master->recorder.ts_beg;
  //master->recorder.file_size = utl::file::size(master->recorder.path);

  //---------------------------
}
void Recorder::export_stop(k4n::structure::Sensor* sensor){
  //---------------------------

  //Recorder
  k4a::record& recorder = sensor->device.recorder;
  if(!recorder.is_valid()) return;

  //Flush to file
  recorder.flush();
  recorder.close();

  //---------------------------
}

}
