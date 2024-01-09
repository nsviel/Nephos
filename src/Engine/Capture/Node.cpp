#include "Node.h"

#include <Engine/Engine.h>


namespace eng::capture{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->node_kinect = new eng::kinect::Node(engine);

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



  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_kinect->reset();

  //---------------------------
}


}
