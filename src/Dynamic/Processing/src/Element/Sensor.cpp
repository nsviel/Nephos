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

  this->dyn_struct = node_processing->get_dyn_struct();
  this->prf_dynamic = node_profiler->get_prf_dynamic();

  //---------------------------
}
Sensor::~Sensor(){}

//Main function
void Sensor::init_sensor(dat::base::Sensor* sensor){
  //---------------------------

  prf_dynamic->add_profiler(&sensor->profiler, sensor->name);

  //---------------------------
}
void Sensor::remove_sensor(dat::base::Sensor* sensor){
  //---------------------------

  prf_dynamic->remove_profiler(&sensor->profiler);

  //---------------------------
}
bool Sensor::is_dynamic(utl::base::Element* element){
  //---------------------------

  if(dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(element)){
    return true;
  }
  else if(dat::base::Set* set = dynamic_cast<dat::base::Set*>(element)){
    // Process entities within the current set
    for(int i=0; i<set->list_entity.size(); i++){
      dat::base::Entity* entity = *next(set->list_entity.begin(), i);
      if(dat::base::Sensor* sensor = dynamic_cast<dat::base::Sensor*>(entity)){
        return true;
      }
    }

    // Recursively process nested sets
    for(int i=0; i<set->list_subset.size(); i++){
      dat::base::Set* subset = *next(set->list_subset.begin(), i);
      if(is_dynamic(subset)){
        return true;
      }
    }
  }

  //---------------------------
  return false;
}

}
