#include "Node.h"

#include <Engine/Namespace.h>
#include <Profiler/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace rad{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* rad_panel = add_panel("Radiometry", ICON_FA_FILM, true);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_data = node_engine->get_node_data();
  this->node_profiler = node_engine->get_node_profiler();

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
  node_calibration->loop();

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
