#include "Node.h"

#include <Utility/Namespace.h>
#include <Radiometry/Namespace.h>


namespace rad::correction{

//Constructor / Destructor
Node::Node(rad::Node* node_radio){
  //---------------------------

  this->node_radio = node_radio;
  this->rad_struct = new rad::correction::Structure();
  this->rad_process = new rad::correction::Process(this);
  this->rad_measure = new rad::correction::Measure(this);
  this->rad_model = new rad::correction::Model(this);
  this->rad_io_measure = new rad::correction::io::Measure(this);
  this->rad_io_model = new rad::correction::io::Model(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  rad_process->init();
  rad_measure->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  rad_process->loop();

  //---------------------------
}

}
