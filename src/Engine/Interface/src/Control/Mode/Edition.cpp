#include "Edition.h"

#include <Interface/Namespace.h>
#include <Data/Namespace.h>
#include <Transformation/Namespace.h>


namespace itf::control{

//Constructor / Destructor
Edition::Edition(itf::Node* node_interface){
  //---------------------------

  dat::Node* node_data = node_interface->get_node_data();

  this->itf_struct = node_interface->get_itf_struct();
  this->dat_selection = node_data->get_dat_selection();
  this->dat_set = node_data->get_dat_set();
  this->ope_operation = new ope::Operation();

  //---------------------------
}
Edition::~Edition(){}

//Main function
void Edition::element_forward(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  float speed = itf_struct->control.key_fast ? itf_struct->control.speed_fast : itf_struct->control.speed_translation;
  glm::vec3 translation = glm::vec3(speed, 0, 0);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_backward(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  float speed = itf_struct->control.key_fast ? itf_struct->control.speed_fast : itf_struct->control.speed_translation;
  glm::vec3 translation = glm::vec3(-speed, 0, 0);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_left(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  float speed = itf_struct->control.key_fast ? itf_struct->control.speed_fast : itf_struct->control.speed_translation;
  glm::vec3 translation = glm::vec3(0, -speed, 0);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_right(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  float speed = itf_struct->control.key_fast ? itf_struct->control.speed_fast : itf_struct->control.speed_translation;
  glm::vec3 translation = glm::vec3(0, speed, 0);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_down(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  float speed = itf_struct->control.key_fast ? itf_struct->control.speed_fast : itf_struct->control.speed_translation;
  glm::vec3 translation = glm::vec3(0, 0, speed);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_up(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  float speed = itf_struct->control.key_fast ? itf_struct->control.speed_fast : itf_struct->control.speed_translation;
  glm::vec3 translation = glm::vec3(0, 0, -speed);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_zoom(float value){
  //---------------------------



  //---------------------------
}

//Subfunction
void Edition::select_next(){
  //---------------------------

  dat_selection->select_next_element();

  //---------------------------
}
void Edition::remove_current(){
  dat::base::Set* set = dat_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  dat_set->remove_entity(set, set->active_entity);

  //---------------------------
}

}
