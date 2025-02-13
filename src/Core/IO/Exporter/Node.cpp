#include "Node.h"

#include <Core/Namespace.h>
#include <Data/Namespace.h>
#include <IO/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>

#include "Namespace.h"


namespace io::exp{

//Constructor / Destructor
Node::Node(io::Node* node_io){
  utl::gui::Panel* panel_export = add_panel("Exporter", ICON_FA_FLOPPY_DISK, false);
  //---------------------------

  //Dependancy
  this->node_data = node_io->get_node_data();

  //Child
  this->io_struct = new io::exp::Structure();
  this->io_exporter = new io::exp::Exporter(this);
  this->gui_export = new io::exp::gui::Panel(this, &panel_export->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::gui(){
  //---------------------------

  gui_export->run_panel();

  //---------------------------
}

}
