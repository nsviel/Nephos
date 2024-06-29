#include "Element.h"

#include <Interface/Namespace.h>
#include <Data/Namespace.h>
#include <Operation/Namespace.h>


namespace itf::control{

//Constructor / Destructor
Element::Element(itf::Node* node_interface){
  //---------------------------

  dat::Node* node_data = node_interface->get_node_data();

  this->itf_struct = node_interface->get_itf_struct();
  this->dat_selection = node_data->get_dat_selection();
  this->dat_set = node_data->get_dat_set();
  this->ope_operation = new ope::Operation();

  //---------------------------
}
Element::~Element(){}

//Main function
void Element::element_forward(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  glm::vec3 translation = glm::vec3(itf_struct->control.element_trans, 0, 0);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Element::element_backward(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  glm::vec3 translation = glm::vec3(-itf_struct->control.element_trans, 0, 0);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Element::element_left(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  glm::vec3 translation = glm::vec3(0, -itf_struct->control.element_trans, 0);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Element::element_right(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  glm::vec3 translation = glm::vec3(0, itf_struct->control.element_trans, 0);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Element::element_down(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  glm::vec3 translation = glm::vec3(0, 0, itf_struct->control.element_trans);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Element::element_up(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  glm::vec3 translation = glm::vec3(0, 0, -itf_struct->control.element_trans);
  ope_operation->make_translation(element, translation);

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
