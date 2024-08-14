#include "Node.h"

#include <Core/Namespace.h>
#include <Dynamic/Namespace.h>
#include <Radiometry/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace dyn{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  utl::gui::Panel* panel_player = add_panel("Player", ICON_FA_PLAY, true);
  utl::gui::Panel* panel_stream = add_panel("Stream", ICON_FA_FILM, false);
  //---------------------------

  this->node_core = node_core;
  this->node_data = node_core->get_node_data();
  this->node_radio = node_core->get_node_radio();
  this->node_profiler = node_core->get_node_profiler();
  this->node_operation = node_core->get_node_operation();

  this->dyn_struct = new dyn::Structure();
  this->dyn_player = new dyn::player::Player(this);
  this->dyn_sensor = new dyn::element::Sensor(this);
  this->dyn_ope_cloud = new dyn::cloud::Operation(this);
  this->dyn_ope_image = new dyn::image::Operation(this);
  this->gui_player = new dyn::gui::player::Panel(this, &panel_player->is_open);
  this->gui_stream = new dyn::gui::stream::Panel(this, &panel_stream->is_open);

  //---------------------------
}
Node::~Node(){}

void Node::loop(){
  //---------------------------

  dyn_player->loop();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_player->run_panel();
  gui_stream->run_panel();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  dyn_player->reset();

  //---------------------------
}


}
