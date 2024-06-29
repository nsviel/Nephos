#include "Element.h"

#include <Interface/Namespace.h>
#include <Data/Namespace.h>


namespace itf::control{

//Constructor / Destructor
Element::Element(itf::Node* node_interface){
  //---------------------------

  dat::Node* node_data = node_interface->get_node_data();

  this->itf_struct = node_interface->get_itf_struct();
  this->dat_selection = node_data->get_dat_selection();
  this->dat_set = node_data->get_dat_set();

  //---------------------------
}
Element::~Element(){}

//Main function
void Element::element_forward(){
  //---------------------------


  //---------------------------
}
void Element::element_backward(){
  //---------------------------



  //---------------------------
}
void Element::element_left(){
  //---------------------------


  //---------------------------
}
void Element::element_right(){
  //---------------------------



  //---------------------------
}
void Element::element_down(){
  //---------------------------



  //---------------------------
}
void Element::element_up(){
  //---------------------------



  //---------------------------
}
void Element::element_zoom(float value){
  //---------------------------



  //---------------------------
}

//Subfunction
void Element::select_next(){
  //---------------------------

  dat_selection->select_next_element();

  //---------------------------
}
void Element::remove_current(){
  dat::base::Set* set = dat_selection->get_selected_set();
  //---------------------------

  dat_set->remove_entity(set, set->active_entity);

  //---------------------------
}

}
