#include "Sensor.h"

#include <Dynamic/Processing/Namespace.h>
#include <Profiler/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace dyn::prc::element{

//Constructor / Destructor
Sensor::Sensor(dyn::prc::Node* node_processing){
  //---------------------------

  prf::Node* node_profiler = node_processing->get_node_profiler();
  prf::monitor::Node* node_monitor = node_profiler->get_node_monitor();

  this->dyn_struct = node_processing->get_dyn_struct();
  this->prf_monitor = node_monitor->get_prf_manager();

  //---------------------------
}
Sensor::~Sensor(){}

//Main function
void Sensor::init_sensor(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  prf_monitor->add_profiler(&sensor->profiler, sensor->name);

  //---------------------------
}
void Sensor::remove_sensor(std::shared_ptr<dat::base::Sensor> sensor){
  //---------------------------

  prf_monitor->remove_profiler(&sensor->profiler);

  //---------------------------
}
bool Sensor::is_dynamic(std::shared_ptr<utl::base::Element> element){
  //---------------------------
/*
  if(std::shared_ptr<dat::base::Sensor> sensor = dynamic_cast<std::shared_ptr<dat::base::Sensor>&>(element)){
    return true;
  }
  else if(std::shared_ptr<dat::base::Set> set = dynamic_cast<std::shared_ptr<dat::base::Set>>(element)){
    // Process entities within the current set
    for(auto& entity : set->list_entity){
      auto sensor = std::dynamic_pointer_cast<dat::base::Sensor>(entity);
      if(sensor){
        return true;
      }
    }

    // Recursively process nested sets
    for(auto& subset : set->list_subset){
      if(is_dynamic(subset)){
        return true;
      }
    }
  }
*/
  //---------------------------
  return false;
}

}
