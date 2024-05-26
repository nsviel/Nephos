#include "Node.h"

#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace ldr{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* panel_loader = add_panel("Loader", ICON_FA_FOLDER, false);
  utl::gui::Panel* panel_export = add_panel("Exporter", ICON_FA_FOLDER, false);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_data = node_engine->get_node_data();

  //Child
  this->ldr_importer = new ldr::io::Importer(this);
  this->ldr_exporter = new ldr::io::Exporter(this);
  this->ldr_recorder = new ldr::io::Recorder(this);
  this->ldr_playback = new ldr::io::Playback(this);
  this->ldr_bookmark = new ldr::bookmark::Manager(this);
  this->gui_loader = new ldr::gui::Loader(this, &panel_loader->is_open);
  this->gui_exporter = new ldr::gui::Exporter(this, &panel_export->is_open);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  ldr_bookmark->init();

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

  gui_loader->run_panel();
  gui_exporter->run_panel();

  //---------------------------
}
void Node::reset(){
  //---------------------------


  //---------------------------
}


}
