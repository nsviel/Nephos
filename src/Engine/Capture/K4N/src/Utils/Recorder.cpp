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

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::make_cloud_export(k4n::dev::Sensor* sensor){
  string& path_dir = sensor->master->operation.export_path_dir;
  //---------------------------

  //Check if directory exists, if not create it
  if(!directory::is_dir_exist(path_dir)){
    directory::create_new(path_dir);
  }


  //---------------------------
}

}
