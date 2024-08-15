#include "Node.h"

#include <Core/Namespace.h>
#include <Data/Namespace.h>


namespace prc{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------


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
