#include "Node.h"

#include <Core/Namespace.h>
#include <Operation/Namespace.h>


namespace ope{

//Constructor / Destructor
Node::Node(core::Node* node_core){
  //---------------------------

  this->node_core = node_core;
  this->ope_struct = new ope::Structure();
  this->gui_panel = new ope::gui::Panel(this);

  //---------------------------
}
Node::~Node(){}

//Main function

//Subfunction

}
