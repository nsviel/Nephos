#include "Node.h"

#include <Core/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Radiometry/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dyn{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  this->node_core = node_core;
  this->node_data = node_core->get_node_data();
  this->node_radio = node_core->get_node_radio();
  this->node_profiler = node_core->get_node_profiler();

  this->dyn_struct = new dyn::Structure();
  this->dyn_sensor = new dyn::element::Sensor(this);
  this->dyn_ope_cloud = new dyn::cloud::Operation(this);
  this->dyn_ope_image = new dyn::image::Operation(this);

  //---------------------------
}
Node::~Node(){}

void Node::loop(){
  //---------------------------


  //---------------------------
}
void Node::gui(){
  //---------------------------


  //---------------------------
}
void Node::reset(){
  //---------------------------


  //---------------------------
}


}
