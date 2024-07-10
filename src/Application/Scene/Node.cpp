#include "Node.h"

#include <Application/Node.h>
#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Kinect/Namespace.h>


namespace sce{

//Constructor / Destructor
Node::Node(app::Node* node_app){
  //---------------------------

  //Dependancy
  this->node_engine = node_app->get_node_engine();
  this->node_kinect = new k4n::Node(node_engine);

  //Child
  this->sce_init = new sce::Init(this);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  sce_init->init();
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
void Node::reset(){
  //---------------------------



  //---------------------------
}


}
