#include "Node.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::model{

//Constructor / Destructor
Node::Node(rad::Node* node_radio){
  //---------------------------

  this->rad_struct = new rad::model::Structure();
  this->model_sphere = new rad::model::sphere::Model(this);
  this->model_chart = new rad::model::chart::Model(this);

  //---------------------------
}
Node::~Node(){}

//Main function



}
