#include "Sensor.h"

#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>


namespace dyn::element{

//Constructor / Destructor
Sensor::Sensor(dyn::Node* node_dynamic){
  //---------------------------

  eng::Node* node_engine = node_dynamic->get_node_engine();

  this->dyn_struct = node_dynamic->get_dyn_struct();

  //---------------------------
}
Sensor::~Sensor(){}

//Main function


}
