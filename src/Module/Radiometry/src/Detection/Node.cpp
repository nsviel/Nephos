#include "Node.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Operation/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Data/Namespace.h>


namespace rad::detection{

//Constructor / Destructor
Node::Node(rad::Node* node_radio){
  //---------------------------

  dat::Node* node_data = node_radio->get_node_data();

  this->node_radio = node_radio;
  this->rad_struct = new rad::detection::Structure();
  this->sphere_process = new rad::detection::sphere::Process(this);
  this->chart_process = new rad::detection::chart::Process(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  sphere_process->init();
  chart_process->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  sphere_process->loop();
  chart_process->loop();

  //---------------------------
}

}
