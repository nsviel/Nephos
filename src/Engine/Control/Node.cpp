#include "Node.h"

#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Control/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ctl{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_camera = node_engine->get_node_camera();
  this->node_data = node_engine->get_node_data();
  this->node_dynamic = node_engine->get_node_dynamic();

  //Child
  this->ctl_struct = new ctl::Structure();
  this->ctl_navigation = new ctl::mode::Navigation(this);
  this->ctl_edition = new ctl::mode::Edition(this);
  this->ctl_player = new ctl::Player(this);
  this->ctl_wheel = new ctl::Wheel(this);
  this->gui_control = new ctl::gui::Control(this);

  //---------------------------
}
Node::~Node(){}

}
