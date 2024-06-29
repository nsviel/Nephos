#include "Element.h"

#include <Interface/Namespace.h>


namespace itf::control{

//Constructor / Destructor
Element::Element(itf::Node* node_interface){
  //---------------------------

  this->itf_struct = node_interface->get_itf_struct();

  //---------------------------
}
Element::~Element(){}

//Main function


}
