#include "Node.h"

#include <Engine/Namespace.h>
#include <Profiler/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Data/Namespace.h>
#include <Module/Node.h>


namespace rad{

//Constructor / Destructor
Node::Node(mod::Node* node_module){
  utl::gui::Panel* rad_panel = add_panel("Radiometry", ICON_FA_FILM, true);
  //---------------------------

  //Dependancy
  this->node_engine = node_module->get_node_engine();
  this->node_data = node_engine->get_node_data();
  this->node_profiler = node_engine->get_node_profiler();

  //Child
  this->rad_struct = new rad::Structure();
  this->rad_detection = new rad::Detection(this);
  this->rad_model = new rad::Model(this);
  this->rad_hough = new rad::detection::Hough(this);
  this->rad_ransac = new rad::detection::Ransac(this);
  this->rad_identification = new rad::detection::Identification(this);
  this->rad_measure = new rad::model::Measure(this);
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


  //---------------------------
}
void Node::loop(){
  //---------------------------



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
