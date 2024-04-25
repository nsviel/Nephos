#include "Node.h"

#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Profiler/Namespace.h>
#include <Radiometry/Namespace.h>


namespace eng::capture{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_scene = node_engine->get_node_scene();
  this->node_profiler = node_engine->get_node_profiler();

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::config(){
  //---------------------------


  //---------------------------
}
void Node::init(){
  //---------------------------


  //---------------------------
}
void Node::loop(){
  //---------------------------



  //---------------------------
}
void Node::gui(){
  //---------------------------



  //---------------------------
}
void Node::clean(){
  //---------------------------


  //---------------------------
}


}
