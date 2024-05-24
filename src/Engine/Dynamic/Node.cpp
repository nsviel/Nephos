#include "Node.h"

#include <Engine/Namespace.h>
#include <Dynamic/Namespace.h>
#include <image/IconsFontAwesome6.h>
#include <Radiometry/Namespace.h>


namespace dyn{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* panel_player = add_panel("Player", ICON_FA_PLAY, true);
  utl::gui::Panel* panel_stream = add_panel("Stream", ICON_FA_FILM, false);
  //---------------------------

  this->node_engine = node_engine;
  this->node_data = node_engine->get_node_data();
  this->node_radio = new rad::Node(node_engine);

  this->dyn_struct = new dyn::Structure();
  this->dyn_ope_cloud = new dyn::cloud::Operation(this);
  this->dyn_ope_image = new dyn::image::Operation(this);
  this->gui_player = new dyn::gui::Player(this, &panel_player->is_open);
  this->gui_stream = new dyn::gui::Stream(this, &panel_stream->is_open);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  node_radio->init();

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

  node_radio->gui();
  gui_player->run_panel();
  gui_stream->run_panel();

  //---------------------------
}
void Node::reset(){
  //---------------------------


  //---------------------------
}


}
