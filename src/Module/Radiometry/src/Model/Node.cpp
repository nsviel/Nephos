#include "Node.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::model{

//Constructor / Destructor
Node::Node(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = new rad::model::Structure();
  this->rad_model = new rad::model::sphere::Model(this);
  this->rad_plot = new rad::model::sphere::Plot(this);
  this->rad_measure = new rad::model::sphere::Measure(this);

  //---------------------------
}
Node::~Node(){}

//Main function



}
