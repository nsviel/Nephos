#include "Node.h"
#include "Namespace.h"

#include <Data/Namespace.h>


namespace dat::atr{

//Constructor / Destructor
Node::Node(dat::Node* node_data){
  //---------------------------

  this->node_graph = node_data->get_node_graph();
  this->atr_struct = new dat::atr::Structure();
  this->gui_attribut = new dat::atr::gui::Panel(this);

  //---------------------------
}
Node::~Node(){}

}
