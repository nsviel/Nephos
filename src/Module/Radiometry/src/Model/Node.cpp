#include "Node.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::model{

//Constructor / Destructor
Node::Node(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = node_radio->get_rad_struct();
  this->rad_model = new rad::model::sphere::Model(node_radio);
  this->rad_plot = new rad::model::sphere::Plot(node_radio, rad_model);
  this->rad_measure = new rad::model::sphere::Measure(node_radio, rad_plot);

  //---------------------------
}
Node::~Node(){}

//Main function



}
