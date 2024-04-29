#include "Node.h"

#include <Engine/Namespace.h>
#include <Graph/Namespace.h>
#include <Kinect/Namespace.h>
#include <Velodyne/Namespace.h>


namespace eng::capture{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_scene = node_engine->get_node_scene();
  this->node_profiler = node_engine->get_node_profiler();

  //Child
  this->node_k4n = new k4n::Node(this);
  this->node_velodyne = new vld::Node(this);

  this->add_node_panel(node_k4n);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::config(){
  //---------------------------

  node_k4n->config();
  //node_velodyne->config();

  //---------------------------
}
void Node::init(){
  //---------------------------

  node_k4n->init();
  //node_velodyne->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_k4n->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_k4n->gui();
  //node_velodyne->gui();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_k4n->clean();
  //node_velodyne->clean();

  //---------------------------
}


}
