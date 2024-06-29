#include "Element.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#include <Interface/Namespace.h>
#include <Operation/Namespace.h>
#include <glm/glm.hpp>


namespace itf::gui{

//Constructor / Destructor
Element::Element(itf::Node* node_interface){
  //---------------------------

  dat::Node* node_data = node_interface->get_node_data();

  this->dat_selection = node_data->get_dat_selection();
  this->dat_set = node_data->get_dat_set();
  this->ope_operation = new ope::Operation();
  this->itf_wheel = node_interface->get_itf_wheel();
  this->itf_element = node_interface->get_itf_element();

  //---------------------------
}
Element::~Element(){}

//Main function
void Element::run_control(){
  //---------------------------

  this->control_keyboard_oneAction();
  this->control_keyboard_translation();
  this->control_wheel();

  //---------------------------
}

//Keyboard
void Element::control_keyboard_oneAction(){
  //----------------------------

  //Tab key
  if(ImGui::IsKeyPressed(ImGuiKey_Tab)) itf_element->select_next();

  //Suppr key - Delete selected
  if(ImGui::IsKeyPressed(ImGuiKey_Delete)) itf_element->remove_current();

  //----------------------------
}
void Element::control_keyboard_translation(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  if(io.MouseDown[1]) return;

  utl::base::Element* element = dat_selection->get_selected_element();

  //Shift speed up
  float translation_qtt = 0.01;
  if(io.KeysDown[340]){
    //translation_qtt = cloud_trans_speed * 5;
  }

  // Z key
  if(io.KeysDown[571]){
    glm::vec3 translation = glm::vec3(translation_qtt, 0, 0);
    ope_operation->make_translation(element, translation);

  }
  // S key
  if(io.KeysDown[564]){
    glm::vec3 translation = glm::vec3(-translation_qtt, 0, 0);
    ope_operation->make_translation(element, translation);

  }
  // D key
  if(io.KeysDown[549]){
    glm::vec3 translation = glm::vec3(0, translation_qtt, 0);
    ope_operation->make_translation(element, translation);

  }
  // Q key
  if(io.KeysDown[562]){
    glm::vec3 translation = glm::vec3(0, -translation_qtt, 0);
    ope_operation->make_translation(element, translation);

  }
  // A key
  if(io.KeysDown[546]){
    glm::vec3 translation = glm::vec3(0, 0, translation_qtt);
    ope_operation->make_translation(element, translation);

  }
  // E key
  if(io.KeysDown[550]){
    glm::vec3 translation = glm::vec3(0, 0, -translation_qtt);
    ope_operation->make_translation(element, translation);

  }

  //----------------------------
}

//Mouse
void Element::control_wheel(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel click - Change mouse wheel mode
  if(ImGui::IsMouseClicked(2)){
    itf_wheel->change_mode();
  }

  //Wheel actions
  if(!io.MouseDown[1] && io.MouseWheel){
    float direction = math::sign(io.MouseWheel);
    itf_wheel->make_action(direction);
  }

  //----------------------------
}


}
