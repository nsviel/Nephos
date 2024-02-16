#include "Node.h"

#include <Utility/Namespace.h>
#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Camera/Namespace.h>


namespace eng::ope{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_utility = node_engine->get_node_utility();
  this->node_scene = node_engine->get_node_scene();
  this->node_camera = node_engine->get_node_camera();

  //Child
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
