#include "Node.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ctr{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_camera = node_engine->get_node_camera();
  this->node_data = node_engine->get_node_data();

  //Child
  this->ctr_struct = new ctr::Structure();
  this->ctr_navigation = new ctr::mode::Navigation(this);
  this->ctr_edition = new ctr::mode::Edition(this);
  this->ctr_player = new ctr::Player(this);
  this->ctr_wheel = new ctr::Wheel(this);
  this->gui_control = new ctr::gui::Control(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::reset(){
  //---------------------------

  this->root->reset();

  //---------------------------
}
void Node::close(){
  //---------------------------

  this->root->close();

  //---------------------------
}

}
