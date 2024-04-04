#include "Node.h"

#include <Engine/Namespace.h>
#include <Capture/Namespace.h>
#include <Scene/Namespace.h>
#include <Velodyne/Namespace.h>



namespace velodyne{

//Constructor / Destructor
Node::Node(eng::capture::Node* node_capture){
  utl::gui::Panel* panel_player = add_panel("Player", ICON_FA_PLAY, true);
  //---------------------------

  this->velo_struct = new velodyne::structure::Main();
  this->node_engine = node_capture->get_node_engine();
  this->node_scene = node_engine->get_node_scene();
  //this->velo_capture = new velodyne::Capture();
  this->gui_player = new velodyne::gui::Player(this, &panel_player->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::config(){
  eng::scene::Format* sce_format = node_scene->get_scene_format();
  //---------------------------

  sce_format->insert_importer(new velodyne::Importer(velo_struct));

  //---------------------------
}
void Node::init(){
  //---------------------------



  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_player->run_panel();

  //---------------------------
}

}
