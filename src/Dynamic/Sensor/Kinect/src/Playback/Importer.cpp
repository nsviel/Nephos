#include "Importer.h"

#include <Kinect/Namespace.h>
#include <IO/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Importer::Importer(k4n::Node* node_k4n){
  //---------------------------

  this->node_io = node_k4n->get_node_io();
  this->node_k4n = node_k4n;
  this->k4n_utils = new k4n::Utils(node_k4n);
  this->k4n_config = new k4n::playback::Configuration(node_k4n);

  this->format = ".mkv";
  this->require_discrete_gpu = true;

  //---------------------------
  this->insert_importer();
}
Importer::~Importer(){}

//Main function
void Importer::insert_importer(){
  //---------------------------

  io::imp::Node* node_importer = node_io->get_node_importer();
  io::imp::Importer* io_importer = node_importer->get_io_importer();
  io_importer->insert_importer(this);

  //---------------------------
}

//Subfunction
std::shared_ptr<utl::base::Element> Importer::import(utl::base::Path path){
  if(!utl::file::is_exist(path.build())) return nullptr;
  //---------------------------

  //Create sensor
  std::shared_ptr<k4n::playback::Sensor> sensor = std::make_shared<k4n::playback::Sensor>(node_k4n, path);

  //Insert sensor into data tree
  k4n_utils->insert_in_kinect_set(*sensor);

  //Start sensor
  sensor->start();

  //---------------------------
  return sensor;
}

}
