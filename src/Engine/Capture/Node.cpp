#include "Node.h"

#include <Engine/Namespace.h>


namespace eng::capture{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  this->node_k4n = new eng::k4n::Node(node_engine);
  this->tasker_cpu = node_engine->get_tasker_cpu();

  this->add_node_panel(node_k4n);

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
