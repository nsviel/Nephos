#include "Node.h"

#include <Engine/Namespace.h>
#include <Profiler/Namespace.h>
#include <Radiometry/Namespace.h>
#include <Capture/Namespace.h>


namespace mod{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_profiler = node_engine->get_node_profiler();
  this->node_radio = new rad::Node(node_engine);
  this->node_capture = new cap::Node(node_engine);

  this->add_node_panel(node_capture);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::config(){
  //---------------------------

  node_capture->config();

  //---------------------------
}
void Node::init(){
  //---------------------------

  node_capture->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_capture->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_radio->gui();
  node_capture->gui();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_capture->clean();

  //---------------------------
}


}
