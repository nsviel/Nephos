#include "Node.h"

#include <System/Namespace.h>
#include <Profiler/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace prf{

Node::Node(sys::Node* node_system){
  utl::gui::Panel* prf_panel = add_panel("Profiler", ICON_FA_ARROW_ROTATE_RIGHT, true);
  //---------------------------

  //Dependancy
  this->node_vulkan = node_system->get_node_vulkan();

  //Child
  this->node_monitor = new prf::monitor::Node(this);
  this->node_hardware = new prf::hardware::Node(this);
  this->gui_panel = new prf::gui::Panel(this, &prf_panel->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  node_hardware->init();
  node_monitor->init();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_panel->run_panel();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_monitor->loop();

  //---------------------------
}


}
