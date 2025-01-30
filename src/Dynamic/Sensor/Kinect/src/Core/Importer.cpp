#include "Importer.h"

#include <Kinect/Namespace.h>
#include <IO/Namespace.h>


namespace k4n{

//Constructor / Destructor
Importer::Importer(k4n::Node* node_k4n){
  //---------------------------

  io::Node* node_io = node_k4n->get_node_io();

  this->node_k4n = node_k4n;
  this->node_importer = node_io->get_node_importer();
  this->k4n_factory = new k4n::Factory(node_k4n);

  //---------------------------
  this->insert_importer();
}
Importer::~Importer(){}

//Main function
void Importer::insert_importer(){
  //---------------------------

  //Set kinect reference
  this->format.name = "Kinect Azure Depth Camera";
  this->format.vendor = "045e";
  this->format.product = "097b";
  this->format.ascii = ".mkv";

  //Insert importer in engine
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
std::shared_ptr<utl::base::Element> Importer::capture(){
  //---------------------------

  //Create sensor
  std::shared_ptr<k4n::capture::Sensor> sensor = k4n_factory->create_capture_sensor();

  //Start sensor
  sensor->start();

  //---------------------------
  return sensor;
}

}
