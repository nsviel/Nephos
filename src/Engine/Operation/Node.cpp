#include "Node.h"

#include <Engine/Operation/Namespace.h>


namespace eng::ope{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->ope_wheel = new eng::ope::Wheel(this);
  this->gui_control = new eng::ope::gui::Control(this);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------



  //---------------------------
}
void Node::gui(){
  //---------------------------



  //---------------------------
}
void Node::control(){
  //---------------------------

  gui_control->run_control();

  //---------------------------
}
void Node::reset(){
  //---------------------------



  //---------------------------
}


}
