#include "Node.h"

#include <Engine/Operation/Namespace.h>


namespace eng::ope{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  this->ope_control = new eng::ope::gui::Control(node_engine);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------



  //---------------------------
}
void Node::loop(){
  //---------------------------


  //---------------------------
}
void Node::control(){
  //---------------------------

  ope_control->run_control();

  //---------------------------
}
void Node::reset(){
  //---------------------------



  //---------------------------
}


}
