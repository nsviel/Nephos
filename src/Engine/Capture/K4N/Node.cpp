#include "Node.h"

#include <Engine/Namespace.h>
#include <K4N/Namespace.h>
#include <Capture/Namespace.h>
#include <Scene/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace k4n{

//Constructor / Destructor
Node::Node(eng::capture::Node* node_capture){
  utl::gui::Panel* ply_panel = add_panel("Player", ICON_FA_PLAY, true);
  utl::gui::Panel* str_panel = add_panel("Stream", ICON_FA_FILM, true);
  //---------------------------

  //Dependancy
  this->node_engine = node_capture->get_node_engine();
  this->node_scene = node_capture->get_node_scene();
  this->node_profiler = node_capture->get_node_profiler();

  //Child
  this->thread_pool = new k4n::thread::Pool(100);
  this->struct_k4n = new k4n::structure::Struct_k4n(this);
  this->k4n_swarm = new k4n::dev::Swarm(this);
  this->k4n_connection = new k4n::thread::Connection(this);
  this->gui_stream = new k4n::gui::Stream(this, &str_panel->is_open);
  this->gui_device = new k4n::gui::Player(this, &ply_panel->is_open);
  this->gui_control = new k4n::gui::Control(this);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::config(){
  eng::scene::Format* sce_format = node_scene->get_scene_format();
  //---------------------------

  sce_format->insert_importer(new k4n::Importer(this));

  //---------------------------
}
void Node::init(){
  //---------------------------

  k4n_connection->start_thread();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  k4n_swarm->manage_connected_device();
  k4n_swarm->manage_resynchronization();

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
void Node::clean(){
  //---------------------------

  k4n_swarm->close_all_master();

  //---------------------------
}


}
