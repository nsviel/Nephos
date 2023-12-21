#include "Node.h"

#include <Engine/Engine.h>


namespace eng::capture{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->kinect = new eng::kinect::Kinect(engine);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------


  //---------------------------
}
void Node::loop(){
  //---------------------------

  kinect->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------



  //---------------------------
}
void Node::reset(){
  //---------------------------

  kinect->reset();

  //---------------------------
}


}
