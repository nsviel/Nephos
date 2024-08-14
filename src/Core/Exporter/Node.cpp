#include "Node.h"

#include <Core/Namespace.h>
#include <Element/Namespace.h>
#include <IO/Namespace.h>
#include <Importer/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace io::exp{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* panel_export = add_panel("Exporter", ICON_FA_FLOPPY_DISK, false);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_data = node_engine->get_node_data();
  this->node_dynamic = node_engine->get_node_dynamic();
  this->node_importer = new io::imp::Node(node_engine);

  //Child
  this->io_struct = new io::exp::Structure();
  this->io_exporter = new io::exp::Exporter(this);
  this->gui_export = new io::exp::gui::Panel(this, &panel_export->is_open);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  io_exporter->init_path();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_export->run_panel();

  //---------------------------
}

}
