#include "Node.h"

#include <Application/Node.h>
#include <Core/Namespace.h>
#include <Scene/Namespace.h>
//#include <Kinect/Namespace.h>
#include <RealSense/Namespace.h>
#include <Radiometry/Namespace.h>


namespace sen{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  this->node_core = node_core;
  //this->node_kinect = new k4n::Node(node_core);
  this->node_realsense = new rlx::Node(node_core);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  //node_kinect->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

//  node_kinect->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  //node_kinect->clean();

  //---------------------------
}

}
