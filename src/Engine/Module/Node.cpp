#include "Node.h"

#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Profiler/Namespace.h>
#include <Radiometry/Namespace.h>


namespace eng::module{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_scene = node_engine->get_node_scene();
  this->node_profiler = node_engine->get_node_profiler();
  this->node_radio = new radio::Node(node_engine);

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

  node_radio->gui();

  //---------------------------
}
void Node::clean(){
  //---------------------------


  //---------------------------
}


}
