#include "Node.h"
#include "Namespace.h"

#include <Data/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dat::ply{

//Constructor / Destructor
Node::Node(dat::Node* node_data){
  utl::gui::Panel* panel_player = add_panel("Player", ICON_FA_PLAY, true);
  //---------------------------

  this->node_attribut = node_data->get_node_attribut();
  this->node_graph = node_data->get_node_graph();

  this->dyn_player = new dat::ply::Player(this);
  this->gui_player = new dat::ply::gui::Panel(this, &panel_player->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::loop(){
  //---------------------------

  dyn_player->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_player->run_panel();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  dyn_player->reset();

  //---------------------------
}


}
