#include "Node.h"

#include <Core/Namespace.h>
#include <Profiler/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace rad{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  utl::gui::Panel* rad_panel = add_panel("Radiometry", ICON_FA_FILM, true);
  //---------------------------

  //Dependancy
  this->node_core = node_core;
  this->node_data = node_core->get_node_data();
  this->node_profiler = node_core->get_node_profiler();

  //Child
  this->node_correction = new rad::correction::Node(this);
  this->node_calibration = new rad::calibration::Node(this);
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

  node_correction->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_correction->loop();
  //node_calibration->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_panel->run_panel();

  //---------------------------
}
void Node::clean(){
  //---------------------------


  //---------------------------
}


}
