#include "Node.h"

#include <Element/Namespace.h>
#include <Data/Node.h>


namespace dat{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();

  //Child
  this->node_element = new dat::elm::Node(node_engine);
  this->node_graph = new dat::graph::Node(node_engine);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  node_graph->init();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_graph->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_graph->clean();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_graph->run_panel();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_graph->reset();

  //---------------------------
}


}
