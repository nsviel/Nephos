#include "Node.h"

#include <Sensor/Namespace.h>
#include <Core/Namespace.h>
#include <Realsense/Namespace.h>
#include <IO/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <Engine/Namespace.h>
#include <Importer/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rlx{

//Constructor / Destructor
Node::Node(dyn::sen::Node* node_sensor){
  //---------------------------

  this->node_core = node_sensor->get_node_core();;
  this->node_io = node_core->get_node_io();
  this->node_profiler = node_core->get_node_profiler();
  this->node_data = node_core->get_node_data();

  this->rlx_struct = new rlx::Structure();
  this->rlx_capture = new rlx::Capture(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  rlx_capture->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  rlx_capture->capture();

  //---------------------------
}



}
