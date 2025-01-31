#include "Node.h"

#include <Application/Namespace.h>
#include <Core/Namespace.h>
#include <Data/Namespace.h>

#include <Radiometry/Namespace.h>
#include <LLMR/Namespace.h>


namespace mod{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  this->node_core = node_app->get_node_core();
  this->node_vulkan = node_app->get_node_vulkan();

  this->node_radio = new rad::Node(this);
  this->node_llmr = new llmr::Node(this);

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
  node_llmr->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_radio->gui();

  //---------------------------
}

}
