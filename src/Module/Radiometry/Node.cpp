#include "Node.h"

#include <Kinect/Namespace.h>
#include <Engine/Namespace.h>
#include <Profiler/Namespace.h>
#include <Radiometry/Namespace.h>
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
  this->radio_struct = new rad::Structure();
  this->radio_detection = new rad::Detection(this);
  this->radio_model = new rad::Model(this);
  this->radio_hough = new rad::detection::Hough(this);
  this->radio_ransac = new rad::detection::Ransac(this);
  this->radio_identification = new rad::detection::Identification(this);
  this->radio_measure = new rad::model::Measure(this);
  this->gui_radiometry = new rad::gui::Radiometry(this, &rad_panel->is_open);

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

  gui_radiometry->run_panel();

  //---------------------------
}
void Node::clean(){
  //---------------------------


  //---------------------------
}


}
