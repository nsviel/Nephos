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
  this->node_dynamic = node_engine->get_node_dynamic();

  //Child
  this->rad_struct = new rad::Structure();
  this->rad_detection = new rad::detection::Manager(this);
  this->rad_model = new rad::model::sphere::Manager(this);
  this->rad_correction = new rad::correction::Manager(this);
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

  //rad_measure->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  rad_detection->loop();

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
