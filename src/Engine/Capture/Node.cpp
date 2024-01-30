#include "Node.h"

#include <Engine/Node.h>
#include <Engine/Capture/Namespace.h>


namespace eng::capture{

//Constructor / Destructor
Node::Node(eng::Node* engine){
  //---------------------------

  this->node_k4n = new eng::k4n::Node(engine);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  node_k4n->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_k4n->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_k4n->gui();

  //---------------------------
}



}
