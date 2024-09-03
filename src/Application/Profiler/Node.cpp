#include "Node.h"

#include <Application/Namespace.h>
#include <Profiler/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace prf{

Node::Node(app::Node* node_app){
  utl::gui::Panel* prf_panel = add_panel("Profiler", ICON_FA_ARROW_ROTATE_RIGHT, true);
  //---------------------------

  //Dependancy
  this->node_vulkan = node_app->get_node_vulkan();

  //Child
  this->node_monitor = new prf::monitor::Node(this);
  this->node_hardware = new prf::hardware::Node(this);
  this->gui_panel = new prf::gui::Panel(this, &prf_panel->is_open);

  //Main cpu tasker
  prf::monitor::Manager* prf_monitor = node_monitor->get_prf_manager();
  this->tasker_cpu = prf_monitor->get_tasker_cpu();

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
