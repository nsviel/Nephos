#include "Node.h"
#include "Namespace.h"

#include <Core/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace eng_{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  this->node_vulkan = node_core->get_node_vulkan();
  this->node_data = node_core->get_node_data();
  this->node_dynamic = node_core->get_node_dynamic();

  this->node_camera = new cam::Node(node_core);
  this->node_control = new ctl::Node(node_core);
  this->node_renderer = new rnd::Node(node_core);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_camera->init();
  node_renderer->init();

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
