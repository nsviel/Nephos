#include "Edition.h"

#include <Interface/Namespace.h>


namespace itf::gui{

//Constructor / Destructor
Edition::Edition(itf::Node* node_interface){
  //---------------------------

  this->itf_struct = node_interface->get_itf_struct();
  this->itf_element = node_interface->get_itf_element();

  //---------------------------
}
Edition::~Edition(){}

//Main function
void Edition::run_control(){
  //---------------------------

  this->control_keyboard_oneAction();
  this->control_keyboard_translation();

  //---------------------------
}

//Keyboard
void Edition::control_keyboard_oneAction(){
  //----------------------------

  //Tab key
  if(ImGui::IsKeyPressed(ImGuiKey_Tab)) itf_element->select_next();

  //Suppr key - Delete selected
  if(ImGui::IsKeyPressed(ImGuiKey_Delete)) itf_element->remove_current();

  //----------------------------
}
void Edition::control_keyboard_translation(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  if(io.MouseDown[1]) return;

  //Shift key
  itf_struct->control.key_fast = (io.KeysDown[340]) ? true : false;

  // Z key
  if(io.KeysDown[571]) itf_element->element_forward();

  // S key
  if(io.KeysDown[564]) itf_element->element_backward();

  // D key
  if(io.KeysDown[549]) itf_element->element_right();

  // Q key
  if(io.KeysDown[562]) itf_element->element_left();

  // A key
  if(io.KeysDown[546]) itf_element->element_down();

  // E key
  if(io.KeysDown[550]) itf_element->element_up();

  //----------------------------
}

}
