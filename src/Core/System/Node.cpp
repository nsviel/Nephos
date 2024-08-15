#include "Node.h"
#include "Namespace.h"


namespace sys{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  this->node_profiler = new prf::Node(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  node_profiler->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_profiler->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_profiler->gui();

  //---------------------------
}

}
