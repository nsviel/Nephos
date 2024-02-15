#include "Importer.h"

#include <K4N/Namespace.h>


namespace format::mkv{

//Constructor / Destructor
Importer::Importer(eng::k4n::Node* node_k4n){
  //---------------------------

  this->k4n_swarm = node_k4n->get_k4n_swarm();

  this->supported_format.push_back("mkv");

  //---------------------------
}
Importer::~Importer(){}

//Main function
void Importer::import(string path){
  //---------------------------

  utl::media::File file;
  file.path_data = path;
  k4n_swarm->create_sensor_playback(file);

  //---------------------------
}


}
