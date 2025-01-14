#include "Node.h"
#include "Namespace.h"

#include <Data/Namespace.h>


namespace dat::atr{

//Constructor / Destructor
Node::Node(dat::Node* node_data){
  utl::gui::Panel* panel = add_panel("Attribut", ICON_FA_ANCHOR, false);
  //---------------------------

  this->node_graph = node_data->get_node_graph();
  this->atr_struct = new dat::atr::Structure();
  this->gui_panel = new dat::atr::gui::Panel(this, &panel->is_open);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::gui(){
  //---------------------------

  gui_panel->run_panel();

  //---------------------------
}

}
