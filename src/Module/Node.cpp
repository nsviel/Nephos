#include "Node.h"

#include <Engine/Namespace.h>
#include <Kinect/Namespace.h>
#include <Radiometry/Namespace.h>


namespace mod{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->node_radio = new rad::Node(this);
  this->node_kinect = new k4n::Node(this);

  this->add_node_panel(node_kinect);
  this->add_node_panel(node_radio);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  node_kinect->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_kinect->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_kinect->clean();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_kinect->gui();
  node_radio->gui();

  //---------------------------
}

}
