#include "Node.h"

#include <Dynamic/Namespace.h>
#include <Core/Namespace.h>
#include <Module/Namespace.h>
#include <Utility/Namespace.h>
#include <Processing/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Engine/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dyn::prc{

//Constructor / Destructor
Node::Node(dyn::Node* node_dynamic){
  //---------------------------

  mod::Node* node_module = node_dynamic->get_node_module();

  this->node_core = node_dynamic->get_node_core();
  this->node_data = node_core->get_node_data();
  this->node_radio = node_module->get_node_radio();
  this->node_profiler = node_core->get_node_profiler();
sayHello();
  this->dyn_struct = new dyn::prc::Structure();sayHello();
  this->dyn_sensor = new dyn::prc::element::Sensor(this);sayHello();
  this->dyn_ope_cloud = new dyn::prc::cloud::Operation(this);sayHello();
  this->dyn_ope_image = new dyn::prc::image::Operation(this);sayHello();

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
