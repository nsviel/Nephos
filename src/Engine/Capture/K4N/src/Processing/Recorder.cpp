#include "Recorder.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>
#include <Scene/Namespace.h>


namespace k4n::processing{

//Constructor / Destructor
Recorder::Recorder(k4n::structure::Struct_k4n* struct_k4n){
  //---------------------------

  eng::scene::Node* node_scene = struct_k4n->node_scene;

  this->struct_k4n = struct_k4n;
  this->sce_exporter = node_scene->get_scene_exporter();
  this->ply_exporter = new format::ply::Exporter();

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::start_thread(k4n::dev::Sensor* sensor){
  //---------------------------

  //Join previous thread
  if(thread_idle && thread.joinable()){
    thread.join();
  }

  //Start new thread
  this->thread_idle = false;
  this->thread = std::thread(&Recorder::run_thread, this, sensor);

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

  tasker->loop_end();
  if(!master->player.record){
    tasker->clear();
  }

  //---------------------------
  this->thread_idle = true;
}
void Recorder::wait_thread(){
  //---------------------------

  while(thread_idle == false){say("wait");
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  //---------------------------
}

//Subfunction
void Recorder::make_export_to_ply(k4n::dev::Sensor* sensor){
  k4n::dev::Master* master = sensor->master;
  if(!master->player.record) return;
  //---------------------------

  //Check if directory exists, if not create it
  string path_dir = sensor->master->recorder.folder;
  if(!directory::is_dir_exist(path_dir)){
    directory::create_new(path_dir);
  }

  //Sensor parameter
  sensor->recorder.folder = path_dir;
  sensor->recorder.mode = k4n::recorder::PLY;

  //Path
  string master_name = master->recorder.filename;
  string sensor_idx = to_string(sensor->param.index);
  string cloud_idx = to_string(sensor->param.index_cloud);
  string filename = master_name + "_" + sensor_idx + "_" + cloud_idx;
  string path = path_dir + "/" + filename + ".ply";

  //Export to ply
  ply_exporter->export_binary(sensor->get_data(), path);

  //---------------------------
}
void Recorder::make_export_to_mkv(k4n::dev::Sensor* sensor){
  k4a::record& recorder = sensor->recorder.handle;
  k4n::dev::Master* master = sensor->master;
  k4a::capture* capture = sensor->param.capture;
  //---------------------------

  if(master->mode == k4n::dev::PLAYBACK) return;

  //Start recording
  if(master->player.record && !recorder.is_valid()){
    //Check if directory exists, if not create it
    string path_dir = sensor->master->recorder.folder;
    if(!directory::is_dir_exist(path_dir)){
      directory::create_new(path_dir);
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
    master->recorder.ts_beg = master->player.ts_cur;
    sensor->recorder.folder = master->recorder.folder;
  }

  //Recording
  else if(master->player.record && recorder.is_valid()){
    recorder.write_capture(*capture);
    master->recorder.ts_rec = master->player.ts_cur - master->recorder.ts_beg;
    master->recorder.file_size = utl::fct::info::get_file_size(master->recorder.path);
  }

  //Flush to file when finish
  else if(!master->player.record && recorder.is_valid()){
    recorder.flush();
    recorder.close();
  }

  //---------------------------
}

}
