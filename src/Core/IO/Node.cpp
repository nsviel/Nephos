#include "Node.h"

#include <Core/Namespace.h>
#include <Element/Namespace.h>
#include <IO/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace io{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* panel_loader = add_panel("Loader", ICON_FA_DOWNLOAD, false);
  utl::gui::Panel* panel_export = add_panel("Exporter", ICON_FA_FLOPPY_DISK, false);
  utl::gui::Panel* panel_transfo = add_panel("Transformation", ICON_FA_PEN_TO_SQUARE, false);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_data = node_engine->get_node_data();
  this->node_dynamic = node_engine->get_node_dynamic();

  //Child
  this->io_struct = new io::Structure();
  this->io_import_ope = new io::importer::Operation(this);
  this->io_importer = new io::Importer(this);
  this->io_exporter = new io::Exporter(this);
  this->io_bookmark = new io::bookmark::Manager(this);
  this->io_transformation = new io::Transformation(this);
  this->gui_import = new io::gui::importer::Panel(this, &panel_loader->is_open);
  this->gui_export = new io::gui::exporter::Panel(this, &panel_export->is_open);
  this->gui_transformation = new io::gui::transformation::Panel(this, &panel_transfo->is_open);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  io_bookmark->init();
  io_importer->init_path();
  io_exporter->init_path();
  io_transformation->init_path();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_import->run_panel();
  gui_export->run_panel();
  gui_transformation->run_panel();

  //---------------------------
}

}
