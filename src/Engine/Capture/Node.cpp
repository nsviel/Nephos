#include "Node.h"

#include <Engine/Namespace.h>


namespace eng::capture{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  this->node_k4n = new eng::k4n::Node(node_engine);
  this->cpu_profiler = node_engine->get_cpu_profiler();

  this->add_node_panel(node_k4n);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  node_k4n->init();

  //---------------------------
}
void Node::loop(){
  cpu_profiler->task_begin("eng::capture");
  //---------------------------

  node_k4n->loop();

  //---------------------------
  cpu_profiler->task_end("eng::capture");
}
void Node::gui(){
  //---------------------------

  node_k4n->gui();

  //---------------------------
}



}
