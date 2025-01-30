#include "Importer.h"

#include <Realsense/Namespace.h>
#include <IO/Namespace.h>


namespace rlx{

//Constructor / Destructor
Importer::Importer(rlx::Node* node_realsense){
  //---------------------------

  io::Node* node_io = node_realsense->get_node_io();

  this->node_realsense = node_realsense;
  this->node_importer = node_io->get_node_importer();
  this->rlx_factory = new rlx::Factory(node_realsense);

  //---------------------------
  this->insert_importer();
}
Importer::~Importer(){}

//Main function
void Importer::insert_importer(){
  //---------------------------

  //Set kinect reference
  this->format.name = "Intel RealSense Depth Camera 455";
  this->format.vendor = "8086";
  this->format.product = "0b5c";
  this->format.ascii = ".bag";

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
  std::shared_ptr<rlx::playback::Sensor> sensor = rlx_factory->create_playback_sensor(path);

  //Start sensor
  sensor->start();

  //---------------------------
  return sensor;
}
std::shared_ptr<utl::base::Element> Importer::capture(){
  //---------------------------

  //Create sensor
  std::shared_ptr<rlx::capture::Sensor> sensor = rlx_factory->create_capture_sensor();

  //Start sensor
  sensor->start();

  //---------------------------
  return sensor;
}

}
