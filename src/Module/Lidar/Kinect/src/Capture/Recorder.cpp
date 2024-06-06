#include "Recorder.h"

#include <Engine/Namespace.h>
#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Loader/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Recorder::Recorder(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  ldr::Node* node_loader = node_engine->get_node_loader();

  this->ldr_exporter = node_loader->get_ldr_exporter();
  this->ply_exporter = new format::ply::Exporter();
  this->thread_pool = node_engine->get_thread_pool();
  this->format = "mkv";

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::start_thread(k4n::structure::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Recorder::run_thread(k4n::structure::Sensor* sensor){
  //prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("recorder");
  //---------------------------
/*
  tasker->loop_begin();

  dat::base::Set* set = sensor->set_parent;
  switch(master->recorder.mode){
    case dyn::recorder::MKV:{
      tasker->task_begin("recorder::mkv");
      this->make_export_to_mkv(sensor);
      tasker->task_end("recorder::mkv");
      break;
    }
    case dyn::recorder::PLY:{
      tasker->task_begin("recorder::ply");
      this->make_export_to_ply(sensor);
      tasker->task_end("recorder::ply");
      break;
    }
  }

  if(!sensor->set_parent->record){
    tasker->reset();
  }

  tasker->loop_end();
*/
  //---------------------------
  this->idle = true;
}
void Recorder::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Recorder::make_export_to_ply(k4n::structure::Sensor* sensor){
/*  dat::base::Set* master = sensor->set_parent;
  if(!master->record) return;
  //---------------------------

  //Check if directory exists, if not create it
  string path_dir = sensor->set_parent->recorder.folder;
  if(!utl::directory::is_exist(path_dir)){
    utl::directory::create(path_dir);
  }

  //Sensor parameter
  sensor->set_parent->recorder.folder = path_dir;
  sensor->set_parent->recorder.mode = dyn::recorder::PLY;

  //Path
  string master_name = master->recorder.filename;
  string sensor_idx = to_string(sensor->device.idx_dev);
  string cloud_idx = to_string(sensor->device.idx_cloud);
  string filename = master_name + "_" + sensor_idx + "_" + cloud_idx;
  string path = path_dir + "/" + filename + ".ply";

  //Export to ply
  ply_exporter->export_binary(sensor->get_data(), sensor->get_pose(), path);
*/
  //---------------------------
}
void Recorder::make_export_to_mkv(k4n::structure::Sensor* sensor){
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
