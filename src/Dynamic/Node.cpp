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