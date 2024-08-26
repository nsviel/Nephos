#include "Edition.h"

#include <Engine/Control/Namespace.h>
#include <Engine/Transformation/Namespace.h>
#include <Data/Namespace.h>


namespace ctr::mode{

//Constructor / Destructor
Edition::Edition(ctr::Node* node_control){
  //---------------------------

  dat::Node* node_data = node_control->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();

  this->ctr_struct = node_control->get_ctr_struct();
  this->gph_selection = node_graph->get_gph_selection();
  this->gph_element = node_graph->get_gph_element();
  this->trf_operation = new eng::trf::Operation();

  //---------------------------
}
Edition::~Edition(){}

//Main function
void Edition::element_forward(){
  std::shared_ptr<utl::base::Element> element = gph_selection->get_selected_element();
  //---------------------------

  float speed = ctr_struct->key_fast ? ctr_struct->speed_fast : ctr_struct->speed_translation;
  glm::vec3 translation = glm::vec3(speed, 0, 0);
  trf_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_backward(){
  std::shared_ptr<utl::base::Element> element = gph_selection->get_selected_element();
  //---------------------------

  float speed = ctr_struct->key_fast ? ctr_struct->speed_fast : ctr_struct->speed_translation;
  glm::vec3 translation = glm::vec3(-speed, 0, 0);
  trf_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_left(){
  std::shared_ptr<utl::base::Element> element = gph_selection->get_selected_element();
  //---------------------------

  float speed = ctr_struct->key_fast ? ctr_struct->speed_fast : ctr_struct->speed_translation;
  glm::vec3 translation = glm::vec3(0, -speed, 0);
  trf_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_right(){
  std::shared_ptr<utl::base::Element> element = gph_selection->get_selected_element();
  //---------------------------

  float speed = ctr_struct->key_fast ? ctr_struct->speed_fast : ctr_struct->speed_translation;
  glm::vec3 translation = glm::vec3(0, speed, 0);
  trf_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_down(){
  std::shared_ptr<utl::base::Element> element = gph_selection->get_selected_element();
  //---------------------------

  float speed = ctr_struct->key_fast ? ctr_struct->speed_fast : ctr_struct->speed_translation;
  glm::vec3 translation = glm::vec3(0, 0, speed);
  trf_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_up(){
  std::shared_ptr<utl::base::Element> element = gph_selection->get_selected_element();
  //---------------------------

  float speed = ctr_struct->key_fast ? ctr_struct->speed_fast : ctr_struct->speed_translation;
  glm::vec3 translation = glm::vec3(0, 0, -speed);
  trf_operation->make_translation(element, translation);

  //---------------------------
}
void Edition::element_zoom(float value){
  //---------------------------



  //---------------------------
}

//Subfunction
void Edition::select_next(){
  //---------------------------

  gph_selection->select_next_element();

  //---------------------------
}
void Edition::remove_current(){
  std::shared_ptr<dat::base::Set> set = gph_selection->get_selected_set();
  if(!set) return;
  //---------------------------

  std::shared_ptr<dat::base::Entity> entity = set->active_entity.lock();
  gph_element->remove_entity(set, entity);

  //---------------------------
}

}
