#include "Node.h"

#include <Engine/Namespace.h>
#include <Operation/Namespace.h>


namespace ope{

//Constructor / Destructor
Node::Node(eng::Node* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->ope_struct = new ope::Structure();
  this->gui_panel = new ope::gui::Panel(this);

  //---------------------------
}
Node::~Node(){}

//Main function

//Subfunction

}
