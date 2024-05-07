#include "Recorder.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>
#include <Engine/Namespace.h>
#include <Loader/Namespace.h>
#include <Profiler/Namespace.h>


namespace k4n::processing{

//Constructor / Destructor
Recorder::Recorder(k4n::Node* node_k4n){
  //---------------------------

  eng::Node* node_engine = node_k4n->get_node_engine();
  ldr::Node* node_loader = node_engine->get_node_loader();

  this->ldr_exporter = node_loader->get_exporter();
  this->ply_exporter = new format::ply::Exporter();
  this->thread_pool = node_engine->get_thread_pool();

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::start_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  this->idle = false;
  auto task_function = [this, sensor](){
    this->run_thread(sensor);
  };
  thread_pool->add_task(task_function);

  //---------------------------
}
void Recorder::run_thread(k4n::dev::Sensor* sensor){
  prf::graph::Tasker* tasker = sensor->profiler->get_or_create_tasker("recorder");
  //---------------------------

  tasker->loop_begin();

  k4n::dev::Master* master = sensor->master;
  switch(master->recorder.mode){
    case k4n::recorder::MKV:{
      tasker->task_begin("recorder::mkv");
      this->make_export_to_mkv(sensor);
      tasker->task_end("recorder::mkv");
      break;
    }
    case k4n::recorder::PLY:{
      tasker->task_begin("recorder::ply");
      this->make_export_to_ply(sensor);
      tasker->task_end("recorder::ply");
      break;
    }
  }

  bool is_record = master->get_state_record();
  if(!is_record){
    tasker->reset();
  }

  tasker->loop_end();

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
void Recorder::make_export_to_ply(k4n::dev::Sensor* sensor){
  k4n::dev::Master* master = sensor->master;
  if(!master->get_state_record()) return;
  //---------------------------

  //Check if directory exists, if not create it
  string path_dir = sensor->master->recorder.folder;
  if(!utl::directory::is_exist(path_dir)){
    utl::directory::create(path_dir);
  }

  //Sensor parameter
  sensor->master->recorder.folder = path_dir;
  sensor->master->recorder.mode = k4n::recorder::PLY;

  //Path
  string master_name = master->recorder.filename;
  string sensor_idx = to_string(sensor->param.index);
  string cloud_idx = to_string(sensor->param.index_cloud);
  string filename = master_name + "_" + sensor_idx + "_" + cloud_idx;
  string path = path_dir + "/" + filename + ".ply";

  //Export to ply
  ply_exporter->export_binary(sensor->get_data(), sensor->get_pose(), path);

  //---------------------------
}
void Recorder::make_export_to_mkv(k4n::dev::Sensor* sensor){
  k4a::record& recorder = sensor->param.recorder;
  k4n::dev::Master* master = sensor->master;
  k4a::capture* capture = sensor->param.capture;
  //---------------------------

  //Start recording
  bool is_record = master->get_state_record();
  if(is_record && !recorder.is_valid()){
    //Check if directory exists, if not create it
    string path_dir = sensor->master->recorder.folder;
    if(!utl::directory::is_exist(path_dir)){
      utl::directory::create(path_dir);
    }

    //Create recorder and file, and write header
    string master_name = master->recorder.filename;
    string sensor_idx = to_string(sensor->param.index);
    string filename = master_name + "_" + sensor_idx;
    string path = path_dir + "/" + filename + ".mkv";

    recorder = k4a::record::create(path.c_str(), sensor->param.device, sensor->param.configuration);
    recorder.write_header();

    //Set info
    master->recorder.path = path;
    master->recorder.file_size = 0;
    float& ts_cur = master->get_ts_cur();
    master->recorder.ts_beg = ts_cur;
  }

  //Recording
  else if(is_record && recorder.is_valid()){
    recorder.write_capture(*capture);
    float& ts_cur = master->get_ts_cur();
    master->recorder.ts_rec = ts_cur - master->recorder.ts_beg;
    master->recorder.file_size = utl::file::size(master->recorder.path);
  }

  //Flush to file when finish
  else if(!is_record && recorder.is_valid()){
    recorder.flush();
    recorder.close();
  }

  //---------------------------
}

}
