#include "Node.h"

#include <Dynamic/Namespace.h>


namespace dyn{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  this->node_processing = new dyn::prc::Node(node_core);
  this->node_sensor = new sen::Node(node_core);

  //---------------------------
}
Node::~Node(){}

void Node::loop(){
  //---------------------------


  //---------------------------
}
void Node::gui(){
  //---------------------------


  //---------------------------
}
void Node::reset(){
  //---------------------------


  //---------------------------
}


}
