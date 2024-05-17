#include "Exporter.h"

#include <Engine/Namespace.h>
#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Loader/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::utils{

//Constructor / Destructor
Exporter::Exporter(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  ldr::Node* node_loader = node_engine->get_node_loader();

  this->ldr_exporter = node_loader->get_ldr_exporter();
  this->ply_exporter = new format::ply::Exporter();
  this->thread_pool = node_engine->get_thread_pool();

  //---------------------------
}
Exporter::~Exporter(){}

//Main function
void Exporter::start_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Exporter::run_thread(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("recorder");
  //---------------------------

  tasker->loop_begin();

  k4n::dev::Master* master = sensor->master;
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

  if(!sensor->master->record){
    tasker->reset();
  }

  tasker->loop_end();

  //---------------------------
  this->idle = true;
}
void Exporter::wait_thread(){
  //For external thread to wait this queue thread idle
  //---------------------------

  while(idle == false){
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Exporter::make_export_to_ply(k4n::dev::Sensor* sensor){
  k4n::dev::Master* master = sensor->master;
  if(!master->record) return;
  //---------------------------

  //Check if directory exists, if not create it
  string path_dir = sensor->master->recorder.folder;
  if(!utl::directory::is_exist(path_dir)){
    utl::directory::create(path_dir);
  }

  //Sensor parameter
  sensor->master->recorder.folder = path_dir;
  sensor->master->recorder.mode = dyn::recorder::PLY;

  //Path
  string master_name = master->recorder.filename;
  string sensor_idx = to_string(sensor->device.idx_dev);
  string cloud_idx = to_string(sensor->device.idx_cloud);
  string filename = master_name + "_" + sensor_idx + "_" + cloud_idx;
  string path = path_dir + "/" + filename + ".ply";

  //Export to ply
  ply_exporter->export_binary(sensor->get_data(), sensor->get_pose(), path);

  //---------------------------
}
void Exporter::make_export_to_mkv(k4n::dev::Sensor* sensor){
  k4a::record& recorder = sensor->device.recorder;
  k4n::dev::Master* master = sensor->master;
  k4a::capture* capture = sensor->device.capture;
  //---------------------------

  //Start recording
  if(sensor->master->record && !recorder.is_valid()){
    //Check if directory exists, if not create it
    string path_dir = sensor->master->recorder.folder;
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
    master->recorder.ts_beg = sensor->master->ts_cur;
  }

  //Recording
  else if(sensor->master->record && recorder.is_valid()){
    recorder.write_capture(*capture);
    master->recorder.ts_rec = sensor->master->ts_cur - master->recorder.ts_beg;
    master->recorder.file_size = utl::file::size(master->recorder.path);
  }

  //Flush to file when finish
  else if(!sensor->master->record && recorder.is_valid()){
    recorder.flush();
    recorder.close();
  }

  //---------------------------
}
}
