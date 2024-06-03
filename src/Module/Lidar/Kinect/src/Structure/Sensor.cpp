#include "Sensor.h"

#include <Engine/Namespace.h>
#include <Kinect/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Dynamic/Namespace.h>


namespace k4n::dev{

//Constructor / Destructor
Sensor::Sensor(k4n::Node* node_k4n){
  //---------------------------

  this->node_engine = node_k4n->get_node_engine();

  //---------------------------
}
Sensor::~Sensor(){}

//Main function
void Sensor::init(){
  //---------------------------

  //Profiler
  prf::Node* node_profiler = node_engine->get_node_profiler();
  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  this->profiler = new prf::graph::Profiler(name, "k4n::sensor");
  prf_manager->add_profiler(profiler);

  //Object
  data.topology.type = utl::topology::POINT;
  data.nb_data_max = 10000000;

  //---------------------------
}
void Sensor::clean(){
  //---------------------------

  //Sensor related
  this->stop_thread();
  this->device.transformation.destroy();

  //Profiler related
  if(profiler == nullptr) return;
  prf::Node* node_profiler = node_engine->get_node_profiler();
  prf::Manager* prf_manager = node_profiler->get_prf_manager();
  prf_manager->remove_profiler(profiler);
  this->profiler = nullptr;

  //---------------------------
}



}
