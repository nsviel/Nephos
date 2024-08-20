#include "Node.h"

#include <Dynamic/Namespace.h>
#include <Core/Namespace.h>

//#include <Kinect/Namespace.h>



namespace dyn::sen{

//Constructor / Destructor
Node::Node(dyn::Node* node_dynamic){
  //---------------------------

  this->node_core = node_dynamic->get_node_core();

  //this->node_kinect = new k4n::Node(this);
  this->node_realsense = new rlx::Node(this);
  this->node_velodyne = new vld::Node(this);

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
