#include "Recorder.h"

#include <K4N/Namespace.h>
#include <Utility/Namespace.h>
#include <Scene/Namespace.h>


namespace k4n::utils{

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
void Recorder::make_export_to_ply(k4n::dev::Sensor* sensor){
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
  string filename = sensor->name;
  if(filename == "") filename = "test.ply";
  string path = path_dir + "/" + filename;

  //Export to ply
  ply_exporter->export_binary(sensor->get_data(), path);

  //---------------------------
}

}
