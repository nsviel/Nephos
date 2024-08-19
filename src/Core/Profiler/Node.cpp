#include "Node.h"

#include <Profiler/Namespace.h>
#include <Core/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace prf{

Node::Node(core::Node* node_core){
  utl::gui::Panel* prf_panel = add_panel("Profiler", ICON_FA_ARROW_ROTATE_RIGHT, true);
  //---------------------------

  this->node_core = node_core;
  this->node_vulkan = node_core->get_node_vulkan();

  this->prf_struct = new prf::Structure();
  this->prf_dynamic = new prf::dynamic::Manager(this);
  this->prf_hardware = new prf::hardware::Profiler(this);
  this->gui_panel = new prf::gui::Panel(this, &prf_panel->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  prf_hardware->init();
  prf_dynamic->init();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_panel->run_panel();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  prf_dynamic->loop(120);

  //---------------------------
}


}
