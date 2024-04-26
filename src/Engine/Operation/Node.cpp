#include "Node.h"

#include <Utility/Namespace.h>
#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Camera/Namespace.h>


namespace ope{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_scene = node_engine->get_node_scene();
  this->node_camera = node_engine->get_node_camera();

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



  //---------------------------
}
void Node::reset(){
  //---------------------------



  //---------------------------
}


}
