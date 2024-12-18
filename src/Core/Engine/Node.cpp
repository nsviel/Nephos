#include "Node.h"

#include <Engine/Namespace.h>
#include <Core/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Data/Namespace.h>


namespace eng{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  this->node_vulkan = node_core->get_node_vulkan();
  this->node_data = node_core->get_node_data();

  this->node_camera = new cam::Node(this);
  this->node_control = new ctr::Node(this);
  this->node_renderer = new rnd::Node(this);
  this->node_transfor = new eng::trf::Node(this);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_camera->init();
  node_renderer->init();
  node_transfor->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_camera->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_camera->gui();
  node_renderer->gui();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_camera->reset();

  //---------------------------
}

}
