#include "Node.h"

#include <Application/Node.h>
#include <Core/Namespace.h>
#include <Scene/Namespace.h>
#include <Kinect/Namespace.h>
#include <RealSense/Namespace.h>
#include <Radiometry/Namespace.h>


namespace mod{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  this->node_engine = node_app->get_node_engine();
  this->node_kinect = new k4n::Node(node_engine);
  this->node_realsense = new rlx::Node(node_engine);
  this->node_radio = new rad::Node(node_engine);

  //---------------------------
}
Node::~Node(){}

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

}
