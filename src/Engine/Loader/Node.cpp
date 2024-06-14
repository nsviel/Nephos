#include "Node.h"

#include <Engine/Namespace.h>
#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace ldr{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* panel_loader = add_panel("Loader", ICON_FA_FILE_ARROW_DOWN, false);
  utl::gui::Panel* panel_export = add_panel("Exporter", ICON_FA_DOWNLOAD, false);
  utl::gui::Panel* panel_transfo = add_panel("Transformation", ICON_FA_PEN_TO_SQUARE, true);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_data = node_engine->get_node_data();
  this->node_dynamic = node_engine->get_node_dynamic();

  //Child
  this->ldr_struct = new ldr::Structure();
  this->ldr_import_ope = new ldr::importer::Operation(this);
  this->ldr_importer = new ldr::io::Importer(this);
  this->ldr_export_ope = new ldr::exporter::Operation(this);
  this->ldr_exporter = new ldr::io::Exporter(this);
  this->ldr_bookmark = new ldr::bookmark::Manager(this);
  this->gui_import = new ldr::gui::importer::Panel(this, &panel_loader->is_open);
  this->gui_export = new ldr::gui::exporter::Panel(this, &panel_export->is_open);
  this->gui_transformation = new ldr::gui::transformation::Panel(this, &panel_transfo->is_open);

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

  gui_import->run_panel();
  gui_export->run_panel();

  //---------------------------
}
void Node::reset(){
  //---------------------------


  //---------------------------
}


}
