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
  this->require_discrete_gpu = true;

  //---------------------------
}
Importer::~Importer(){}

//Main function
utl::file::Entity* Importer::import(utl::file::Path path){
  //---------------------------

  k4n_swarm->create_sensor_playback(path);

  //---------------------------
  return nullptr;
}


}
