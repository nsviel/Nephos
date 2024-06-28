#include "Sensor.h"

#include <Utility/Namespace.h>
#include <Profiler/Namespace.h>
#include <Dynamic/Namespace.h>


namespace dyn::element{

//Constructor / Destructor
Sensor::Sensor(dyn::Node* node_dynamic){
  //---------------------------

  prf::Node* node_profiler = node_dynamic->get_node_profiler();

  this->dyn_struct = node_dynamic->get_dyn_struct();
  this->prf_dynamic = node_profiler->get_prf_dynamic();

  //---------------------------
}
Sensor::~Sensor(){}

//Main function
void Sensor::init_sensor(dyn::base::Sensor* sensor){
  //---------------------------

  prf_dynamic->add_profiler(&sensor->profiler, sensor->name);

  //---------------------------
}
void Sensor::remove_sensor(dyn::base::Sensor* sensor){
  //---------------------------

  prf_dynamic->remove_profiler(&sensor->profiler);

  //---------------------------
}

}
