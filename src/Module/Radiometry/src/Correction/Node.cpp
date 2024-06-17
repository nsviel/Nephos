#include "Node.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::correction{

//Constructor / Destructor
Node::Node(rad::Node* node_radio){
  //---------------------------

  this->node_radio = node_radio;
  this->rad_struct = new rad::correction::Structure();
  this->sphere_process = new rad::correction::Process(this);

  //---------------------------
}
Node::~Node(){}

//Main function


}
