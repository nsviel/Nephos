#include "Node.h"

#include <Engine/Engine.h>
#include <Engine/Capture/K4N/Namespace.h>


namespace eng::capture{

//Constructor / Destructor
Node::Node(Engine* engine){
  //---------------------------

  this->k4n_node = new eng::k4n::Node(engine);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  k4n_node->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  k4n_node->loop();

  //---------------------------
}


}
