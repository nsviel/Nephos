#include "Node.h"

#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Velodyne/Namespace.h>
#include <Loader/Namespace.h>


namespace vld{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* panel = add_panel("Velodyne", ICON_FA_PLAY, true);
  //---------------------------

  this->node_engine = node_engine;
  this->node_loader = node_engine->get_node_loader();
  this->node_data = node_engine->get_node_data();

  this->vld_struct = new vld::structure::Main();
  this->vld_capture = new vld::main::Capture(this);
  this->vld_playback = new vld::main::Playback(vld_struct);
  this->gui_velodyne = new vld::gui::Velodyne(vld_struct, &panel->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::config(){
  ldr::io::Importer* ldr_importer = node_loader->get_ldr_importer();
  //---------------------------

  ldr_importer->insert_importer(new vld::utils::Importer(vld_struct));

  //---------------------------
}
void Node::init(){
  //---------------------------

  vld_capture->init();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_velodyne->run_panel();

  //---------------------------
}
void Node::clean(){
  //---------------------------

  vld_playback->stop_playback();
  vld_capture->clean();

  //---------------------------
}

}
