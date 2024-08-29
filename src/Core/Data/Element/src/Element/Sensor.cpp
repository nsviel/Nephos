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

  //---------------------------
}
Sensor::~Sensor(){}

//Main function
void Sensor::init_profiler(dat::base::Sensor& sensor){
  //---------------------------

  prf_monitor->add_profiler(&sensor.profiler, sensor.name);

  //---------------------------
}
void Sensor::clean_sensor(dat::base::Sensor& sensor){
  //---------------------------

  prf_monitor->remove_profiler(&sensor.profiler);

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
