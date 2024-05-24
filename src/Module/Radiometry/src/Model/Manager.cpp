#include "Manager.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::model{

//Constructor / Destructor
Manager::Manager(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_model = new rad::model::Model(node_radio);
  this->rad_plot = new rad::model::Plot(node_radio, rad_model);
  this->rad_measure = new rad::model::Measure(node_radio, rad_plot);

  //---------------------------
}
Manager::~Manager(){}

//Main function



}
