#include "Node.h"

#include <Engine/Namespace.h>
#include <Capture/Namespace.h>
#include <Scene/Namespace.h>
#include <Velodyne/Namespace.h>



namespace vld{

//Constructor / Destructor
Node::Node(eng::capture::Node* node_capture){
  utl::gui::Panel* panel = add_panel("Velodyne", ICON_FA_PLAY, true);
  //---------------------------

  this->vld_struct = new vld::structure::Main();
  vld_struct->thread.playback = new vld::thread::Playback(vld_struct);
  this->vld_player = new vld::processing::Player(vld_struct);
  this->node_engine = node_capture->get_node_engine();
  this->node_scene = node_engine->get_node_scene();
  //this->velo_capture = new vld::Capture();
  this->gui_velodyne = new vld::gui::Velodyne(vld_struct, &panel->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::config(){
  eng::scene::Format* sce_format = node_scene->get_scene_format();
  //---------------------------

  sce_format->insert_importer(new vld::utils::Importer(vld_struct));

  //---------------------------
}
void Node::init(){
  //---------------------------



  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_velodyne->run_panel();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  vld_player->stop_playback();

  //---------------------------
}

}
