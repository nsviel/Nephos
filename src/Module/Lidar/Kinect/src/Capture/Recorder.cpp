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
void Recorder::start_thread(k4n::structure::Sensor* sensor){
  //---------------------------

  if(!thread_running){
    this->thread_running = true;
    this->thread = std::thread(&Recorder::run_thread, this, sensor);
  }

  //---------------------------
}
void Recorder::run_thread(k4n::structure::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler.get_or_create_tasker("recorder");
  //---------------------------

  tasker->loop_begin();

  tasker->task_begin("recorder::mkv");
  this->make_export(sensor);
  tasker->task_end("recorder::mkv");

  tasker->loop_end();

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
void Recorder::make_export(k4n::structure::Sensor* sensor){
  k4a::record& recorder = sensor->device.recorder;
  k4a::capture* capture = sensor->device.capture;
  //---------------------------
/*
  //Start recording
  if(sensor->set_parent->record && !recorder.is_valid()){
    //Check if directory exists, if not create it
    string path_dir = sensor->set_parent->recorder.folder;
    if(!utl::directory::is_exist(path_dir)){
      utl::directory::create(path_dir);
    }

    //Create recorder and file, and write header
    string master_name = master->recorder.filename;
    string sensor_idx = to_string(sensor->device.idx_dev);
    string filename = master_name + "_" + sensor_idx;
    string path = path_dir + "/" + filename + ".mkv";

    recorder = k4a::record::create(path.c_str(), sensor->device.handle, sensor->device.configuration);
    recorder.write_header();

    //Set info
    master->recorder.path = path;
    master->recorder.file_size = 0;
    master->recorder.ts_beg = sensor->set_parent->ts_cur;
  }

  //Recording
  else if(sensor->set_parent->record && recorder.is_valid()){
    recorder.write_capture(*capture);
    master->recorder.ts_rec = sensor->set_parent->ts_cur - master->recorder.ts_beg;
    master->recorder.file_size = utl::file::size(master->recorder.path);
  }

  //Flush to file when finish
  else if(!sensor->set_parent->record && recorder.is_valid()){
    recorder.flush();
    recorder.close();
  }
*/
  //---------------------------
}

}
