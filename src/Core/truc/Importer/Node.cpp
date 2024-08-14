#include "Node.h"

#include <Core/Namespace.h>
#include <Data/Namespace.h>
#include <Importer/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace io::imp{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  utl::gui::Panel* panel_loader = add_panel("Loader", ICON_FA_DOWNLOAD, false);
  //---------------------------

  //Dependancy
  this->node_engine = node_engine;
  this->node_vulkan = node_engine->get_node_vulkan();
  this->node_data = node_engine->get_node_data();
  this->node_dynamic = node_engine->get_node_dynamic();

  //Child
  this->io_struct = new io::imp::Structure();
  this->io_operation = new io::imp::Operation(this);
  this->io_importer = new io::imp::Importer(this);
  this->io_bookmark = new io::imp::Bookmark(this);
  this->gui_import = new io::imp::gui::Panel(this, &panel_loader->is_open);

  //---------------------------
}
Node::~Node(){}

void Node::init(){
  //---------------------------

  io_bookmark->init();
  io_importer->init_path();

  //---------------------------
}
void Node::gui(){
  //---------------------------

  gui_import->run_panel();

  //---------------------------
}

}
