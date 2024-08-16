#include "Node.h"

#include <Core/Namespace.h>
#include <Module/Namespace.h>
#include <System/Namespace.h>
#include <Processing/Namespace.h>
#include <Radiometry/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dyn::prc{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  mod::Node* node_module = node_core->get_node_module();
  sys::Node* node_system = node_core->get_node_system();

  this->node_core = node_core;
  this->node_data = node_core->get_node_data();
  this->node_radio = node_module->get_node_radio();
  this->node_profiler = node_system->get_node_profiler();

  this->dyn_struct = new dyn::prc::Structure();
  this->dyn_sensor = new dyn::prc::element::Sensor(this);
  this->dyn_ope_cloud = new dyn::prc::cloud::Operation(this);
  this->dyn_ope_image = new dyn::prc::image::Operation(this);

  //---------------------------
}
Node::~Node(){}

//Main function
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
