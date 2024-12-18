#include "Node.h"

#include <Dynamic/Namespace.h>

#include <Kinect/Namespace.h>
#include <Realsense/Namespace.h>
#include <Velodyne/Namespace.h>


namespace dyn::sen{

//Constructor / Destructor
Node::Node(dyn::Node* node_dynamic){
  //---------------------------

  this->node_core = node_dynamic->get_node_core();
  this->node_processing = node_dynamic->get_node_processing();

  this->node_kinect = new k4n::Node(this);
  this->node_realsense = new rlx::Node(this);
  this->node_velodyne = new vld::Node(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  //node_velodyne->init();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_velodyne->clean();

  //---------------------------
}

}
