#include "Node.h"

#include <Dynamic/Namespace.h>
#include <Core/Namespace.h>


namespace dyn{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  this->node_core = node_core;
  this->node_module = node_core->get_node_module();
  this->node_processing = new dyn::prc::Node(this);
  this->node_sensor = new sen::Node(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  node_processing->loop();
  node_sensor->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_processing->loop();
  node_sensor->init();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_processing->gui();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_processing->reset();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_sensor->reset();

  //---------------------------
}


}
