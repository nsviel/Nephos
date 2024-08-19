#include "Node.h"

#include <Core/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Data/Graph/Namespace.h>
#include <Data/Player/Namespace.h>
#include <Data/Attribut/Namespace.h>
#include <Data/Image/Namespace.h>


namespace dat{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  //Dependancy
  this->node_core = node_core;
  this->node_vulkan = node_core->get_node_vulkan();

  //Child
  this->node_element = new dat::elm::Node(this);
  this->node_attribut = new dat::atr::Node(this);
  this->node_graph = new dat::gph::Node(this);
  this->node_player = new dat::ply::Node(this);

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
  node_player->loop();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  node_graph->clean();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  node_graph->gui();
  node_player->gui();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_graph->reset();
  node_player->reset();

  //---------------------------
}


}
