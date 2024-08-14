#include "Edition.h"

#include <Control/Namespace.h>
#include <Data/Namespace.h>
#include <Graph/Namespace.h>
#include <Operation/Namespace.h>


namespace ctl::mode{

//Constructor / Destructor
Edition::Edition(ctl::Node* node_control){
  //---------------------------

  dat::Node* node_data = node_control->get_node_data();
  dat::graph::Node* node_graph = node_data->get_node_graph();

  this->ctl_struct = node_control->get_ctl_struct();
  this->dat_selection = node_graph->get_dat_selection();
  this->dat_set = node_data->get_dat_set();
  this->ope_operation = new ope::Operation();

  //---------------------------
}
Edition::~Edition(){}

//Main function
void Edition::element_forward(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  float speed = ctl_struct->key_fast ? ctl_struct->speed_fast : ctl_struct->speed_translation;
  glm::vec3 translation = glm::vec3(speed, 0, 0);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_backward(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  float speed = ctl_struct->key_fast ? ctl_struct->speed_fast : ctl_struct->speed_translation;
  glm::vec3 translation = glm::vec3(-speed, 0, 0);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_left(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  float speed = ctl_struct->key_fast ? ctl_struct->speed_fast : ctl_struct->speed_translation;
  glm::vec3 translation = glm::vec3(0, -speed, 0);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_right(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  float speed = ctl_struct->key_fast ? ctl_struct->speed_fast : ctl_struct->speed_translation;
  glm::vec3 translation = glm::vec3(0, speed, 0);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_down(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  float speed = ctl_struct->key_fast ? ctl_struct->speed_fast : ctl_struct->speed_translation;
  glm::vec3 translation = glm::vec3(0, 0, speed);
  ope_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_up(){
  utl::base::Element* element = dat_selection->get_selected_element();
  //---------------------------

  float speed = ctl_struct->key_fast ? ctl_struct->speed_fast : ctl_struct->speed_translation;
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