#include "Node.h"

#include <Engine/Namespace.h>
#include <Dynamic/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace dyn{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* panel_player = add_panel("Player", ICON_FA_PLAY, true);
  //---------------------------

  this->node_engine = node_engine;
  this->node_data = node_engine->get_node_data();
  this->gui_player = new dyn::gui::Player(this, &panel_player->is_open);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------



  //---------------------------
}
void Node::loop(){
  //---------------------------


  //---------------------------
}
void Node::clean(){
  //---------------------------


  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_player->run_panel();

  //---------------------------
}
void Node::reset(){
  //---------------------------


  //---------------------------
}


}
