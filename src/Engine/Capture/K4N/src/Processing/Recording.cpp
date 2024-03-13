#include "Recording.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>
#include <Scene/Namespace.h>


namespace k4n::thread{

//Constructor / Destructor
Recording::Recording(k4n::structure::Struct_k4n* struct_k4n){
  //---------------------------

  eng::scene::Node* node_scene = struct_k4n->node_scene;

  this->struct_k4n = struct_k4n;
  this->sce_exporter = node_scene->get_scene_exporter();
  this->ply_exporter = new format::ply::Exporter();

  //---------------------------
}
Recording::~Recording(){}

//Main function
void Recording::start_thread(){
  //---------------------------

  if(!thread_running){
    this->thread = std::thread(&Recording::run_thread, this);
  }

  //---------------------------
  this->thread_running = true;
  this->thread_idle = false;
}
void Recording::run_thread(){
  //---------------------------


  //---------------------------
}
void Recording::stop_thread(){
  //---------------------------

  if(thread.joinable()){
    thread.join();
  }

  //---------------------------
  this->thread_idle = true;
}

//Subfunction
void Recording::make_export_to_ply(k4n::dev::Sensor* sensor){
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
  string filename = sensor->name + "_f" + to_string(sensor->param.index_cloud);
  string path = path_dir + "/" + filename + ".ply";

  //Export to ply
  ply_exporter->export_binary(sensor->get_data(), path);

  //---------------------------
}

}
