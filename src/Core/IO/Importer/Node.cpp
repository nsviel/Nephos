#include "Node.h"

#include <IO/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace io::imp{

//Constructor / Destructor
Node::Node(io::Node* node_io){
  utl::gui::Panel* panel_loader = add_panel("Loader", ICON_FA_DOWNLOAD, false);
  //---------------------------

  //Dependancy
  this->node_data = node_io->get_node_data();
  this->node_engine = node_io->get_node_engine();

  //Child
  this->io_struct = new io::imp::Structure();
  this->io_operation = new io::imp::Operation(this);
  this->io_importer = new io::imp::Importer(this);
  this->io_bookmark = new io::imp::Bookmark(this);
  this->gui_import = new io::imp::gui::Panel(this, &panel_loader->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
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
