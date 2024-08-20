#include "Node.h"

#include <Radiometry/Correction/Namespace.h>
#include <Utility/Namespace.h>


namespace rad::cor{

//Constructor / Destructor
Node::Node(rad::Node* node_radio){
  //---------------------------

  this->node_radio = node_radio;
  
  this->rad_struct = new rad::cor::Structure();
  this->rad_process = new rad::cor::Process(this);
  this->rad_model = new rad::cor::Model(this);
  this->rad_plot = new rad::cor::Plot(this);
  this->rad_measure = new rad::cor::Measure(this);
  this->rad_io_measure = new rad::cor::io::Measure(this);
  this->rad_io_model = new rad::cor::io::Model(this);
  this->rad_correction = new rad::cor::Correction(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  rad_process->init();
  rad_measure->init();
  rad_plot->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  rad_process->loop();

  //---------------------------
}

}
