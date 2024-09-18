#include "Node.h"
#include "Namespace.h"

#include <Data/Namespace.h>


namespace dat::atr{

//Constructor / Destructor
Node::Node(dat::Node* node_data){
  //---------------------------

  this->node_element = node_data->get_node_element();
  
  this->atr_struct = new dat::atr::Structure();

  //---------------------------
}
Node::~Node(){}

}
