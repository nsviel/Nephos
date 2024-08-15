#include "Node.h"

#include <Core/Namespace.h>
#include <Operation/Namespace.h>


namespace dat::atr{

//Constructor / Destructor
Node::Node(dat::Node* node_data){
  //---------------------------

  this->node_core = node_core;
  this->atr_struct = new dat::atr::Structure();
  this->gui_panel = new dat::atr::gui::Panel(this);

  //---------------------------
}
Node::~Node(){}

//Main function

//Subfunction

}
