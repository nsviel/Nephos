#include "Node.h"

#include <Application/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Core/Namespace.h>


namespace dyn{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  this->node_core = node_app->get_node_core();
  this->node_module = node_app->get_node_module();
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
