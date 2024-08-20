#include "Node.h"

#include <Application/Namespace.h>

#include <Dynamic/Processing/Namespace.h>
#include <Dynamic/Sensor/Namespace.h>


namespace dyn{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  this->node_core = node_app->get_node_core();
  this->node_module = node_app->get_node_module();
  this->node_processing = new dyn::prc::Node(this);
  this->node_sensor = new dyn::sen::Node(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  node_sensor->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_sensor->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_sensor->clean();

  //---------------------------
}


}
