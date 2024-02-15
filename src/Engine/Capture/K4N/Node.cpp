#include "Node.h"

#include <Engine/Node.h>
#include <K4N/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace eng::k4n{

//Constructor / Destructor
Node::Node(eng::Node* engine){
  utl::gui::Panel* ply_panel = new_panel("Player", ICON_FA_PLAY, true);
  utl::gui::Panel* str_panel = new_panel("Stream", ICON_FA_FILM, true);
  //---------------------------

  this->engine = engine;
  this->k4n_swarm = new eng::k4n::dev::Swarm(this);
  this->k4n_connection = new eng::k4n::dev::Connection(this);
  this->gui_stream = new eng::k4n::gui::Stream(this, &str_panel->is_open);
  this->gui_device = new eng::k4n::gui::Player(this, &ply_panel->is_open);
  this->gui_control = new eng::k4n::gui::Control(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::init(){
  //---------------------------

  k4n_swarm->init_scene();
  k4n_connection->start_thread();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  k4n_swarm->update_profiler();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_device->run_panel();
  gui_stream->run_panel();

  //---------------------------
}
void Node::control(){
  //---------------------------

  gui_control->run_control();

  //---------------------------
}
void Node::exit(){
  //---------------------------

  k4n_swarm->close_all_master();

  //---------------------------
}


}
