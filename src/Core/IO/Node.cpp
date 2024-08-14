#include "Node.h"

#include <Core/Namespace.h>
#include <Element/Namespace.h>
#include <IO/Namespace.h>
#include <Importer/Namespace.h>
#include <Exporter/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace io{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* panel_export = add_panel("Exporter", ICON_FA_FLOPPY_DISK, false);
  utl::gui::Panel* panel_transfo = add_panel("Transformation", ICON_FA_PEN_TO_SQUARE, false);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_data = node_engine->get_node_data();
  this->node_dynamic = node_engine->get_node_dynamic();
  this->node_importer = new io::imp::Node(node_engine);

  //Child
  this->io_struct = new io::Structure();
  this->io_exporter = new io::Exporter(this);
  this->io_transformation = new io::Transformation(this);
  this->gui_export = new io::exp::gui::Panel(this, &panel_export->is_open);
  this->gui_transformation = new io::gui::transformation::Panel(this, &panel_transfo->is_open);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  io_exporter->init_path();
  io_transformation->init_path();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_export->run_panel();
  gui_transformation->run_panel();

  //---------------------------
}

}
