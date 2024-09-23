#include "Sensor.h"

#include <Data/Element/Namespace.h>
#include <Data/Base/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>


namespace dat::elm{

//Constructor / Destructor
Sensor::Sensor(dat::elm::Node* node_element){
  //---------------------------

  prf::Node* node_profiler = node_element->get_node_profiler();
  prf::monitor::Node* node_monitor = node_profiler->get_node_monitor();

  this->prf_monitor = node_monitor->get_prf_manager();
  this->dat_entity = node_element->get_dat_entity();
  
  //---------------------------
}
Sensor::~Sensor(){}

//Main function
void Sensor::init_sensor(dat::base::Sensor& sensor){
  //---------------------------

  prf_monitor->add_profiler(&sensor.profiler, sensor.name);
  dat_entity->init_entity(sensor);

  //---------------------------
}
void Sensor::clean_sensor(dat::base::Sensor& sensor){
  //---------------------------

  prf_monitor->remove_profiler(&sensor.profiler);

  //---------------------------
}

}
