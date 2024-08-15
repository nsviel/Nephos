#include "Node.h"

#include <Radiometry/Namespace.h>
#include <Core/Namespace.h>
#include <Data/Namespace.h>


namespace prc{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  this->node_radio = new rad::Node(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  node_radio->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_radio->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_radio->gui();

  //---------------------------
}

}
