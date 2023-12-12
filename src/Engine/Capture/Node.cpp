#include "Node.h"


namespace eng::capture{

//Constructor / Destructor
Node::Node(){
  //---------------------------

  this->kinect = new util::kinect::Kinect();

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  kinect->init();

  //---------------------------
}
void Node::run(){
  //---------------------------

  //---------------------------
}
void Node::clean(){
  //---------------------------



  //---------------------------
}

}
