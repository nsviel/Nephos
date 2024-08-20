#include "Node.h"

#include <Module/Namespace.h>
#include <Core/Namespace.h>
#include <Utility/Namespace.h>

#include <Radiometry/gui/Namespace.h>
#include <Radiometry/Calibration/Namespace.h>
#include <Radiometry/Correction/Namespace.h>


namespace rad{

//Constructor / Destructor
Node::Node(mod::Node* node_module){
  utl::gui::Panel* rad_panel = add_panel("Radiometry", ICON_FA_FILM, true);
  //---------------------------

  //Dependancy
  this->node_vulkan = node_module->get_node_vulkan();
  this->node_core = node_module->get_node_core();
  this->node_data = node_core->get_node_data();
  this->node_profiler = node_core->get_node_profiler();

  //Child
  this->node_correction = new rad::cor::Node(this);
  this->node_calibration = new rad::cal::Node(this);
  this->gui_panel = new rad::gui::Panel(this, &rad_panel->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::config(){
  //---------------------------


  //---------------------------
}
void Node::init(){
  //---------------------------

  //node_correction->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

//  node_correction->loop();
  //node_calibration->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

//  gui_panel->run_panel();

  //---------------------------
}
void Node::clean(){
  //---------------------------


  //---------------------------
}


}
