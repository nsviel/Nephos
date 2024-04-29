#include "Node.h"

#include <Kinect/Namespace.h>
#include <Engine/Namespace.h>
#include <Graph/Namespace.h>
#include <Profiler/Namespace.h>
#include <Radiometry/Namespace.h>


namespace radio{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* cal_panel = add_panel("Radiometry", ICON_FA_FILM, true);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_scene = node_engine->get_node_scene();
  this->node_profiler = node_engine->get_node_profiler();

  //Child
  this->radio_struct = new radio::Structure(this);
  this->radio_detection = new radio::Detection(radio_struct);
  this->radio_model = new radio::Model(radio_struct);
  this->radio_hough = new radio::detection::Hough(radio_struct);
  this->radio_ransac = new radio::detection::Ransac(radio_struct);
  this->radio_identification = new radio::detection::Identification(radio_struct);
  this->radio_measure = new radio::model::Measure(radio_struct);
  this->gui_radiometry = new radio::gui::Radiometry(radio_struct, &cal_panel->is_open);

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
