#include "Importer.h"

#include <Engine/Namespace.h>
#include <K4N/Namespace.h>


namespace k4n{

//Constructor / Destructor
Importer::Importer(k4n::Node* node_k4n){
  //---------------------------

  this->node_engine = node_k4n->get_node_engine();
  this->k4n_swarm = node_k4n->get_k4n_swarm();

  this->format = "mkv";

  //---------------------------
}
Importer::~Importer(){}

//Main function
utl::media::File* Importer::import(string path){
  //---------------------------

  utl::media::File file;
  file.path_data = path;
  k4n_swarm->create_sensor_playback(file);

  //---------------------------
  return nullptr;
}


}
