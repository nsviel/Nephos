#include "Importer.h"

#include <Kinect/Namespace.h>
#include <IO/Namespace.h>


namespace k4n::playback{

//Constructor / Destructor
Importer::Importer(k4n::Node* node_k4n){
  //---------------------------

  io::Node* node_io = node_k4n->get_node_io();

  this->node_importer = node_io->get_node_importer();
  this->node_k4n = node_k4n;
  this->k4n_factory = new k4n::Factory(node_k4n);
  this->k4n_config = new k4n::playback::Configuration(node_k4n);

  this->reference.format = ".mkv";

  //---------------------------
  this->insert_importer();
}
Importer::~Importer(){}

//Main function
void Importer::insert_importer(){
  //---------------------------

  io::imp::Importer* io_importer = node_importer->get_io_importer();
  io_importer->insert_importer(this);

  //---------------------------
}

//Subfunction
std::shared_ptr<utl::base::Element> Importer::import(utl::base::Path path){
  if(!utl::file::is_exist(path.build())) return nullptr;
  //---------------------------

  //Create sensor
  std::shared_ptr<k4n::playback::Sensor> sensor = k4n_factory->create_playback_sensor(path);

  //Start sensor
  sensor->start();

  //---------------------------
  return sensor;
}
std::shared_ptr<utl::base::Element> Importer::capture(utl::base::Path path){
  if(!utl::file::is_exist(path.build())) return nullptr;
  //---------------------------

  //Create sensor
  std::shared_ptr<k4n::capture::Sensor> sensor = k4n_factory->create_capture_sensor(path);

  //Start sensor
  sensor->start();

  //---------------------------
  return sensor;
}

}
