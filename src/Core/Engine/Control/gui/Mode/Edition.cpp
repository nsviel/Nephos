#include "Edition.h"

#include <Engine/Control/Namespace.h>
#include <Utility/Namespace.h>


namespace ctr::gui{

//Constructor / Destructor
Edition::Edition(ctr::Node* node_control){
  //---------------------------

  this->ctr_struct = node_control->get_ctr_struct();
  this->ctr_edition = node_control->get_ctr_edition();
  this->ctr_wheel = node_control->get_ctr_wheel();

  //---------------------------
}
Edition::~Edition(){}

//Main function
void Edition::run_control(){
  //---------------------------

  this->control_keyboard_oneAction();
  this->control_keyboard_translation();
  this->control_wheel();

  //---------------------------
}

//Subfunction
void Edition::control_keyboard_oneAction(){
  //----------------------------

  //Tab key
  if(ImGui::IsKeyPressed(ImGuiKey_Tab)) ctr_edition->select_next();

  //Suppr key - Delete selected
  if(ImGui::IsKeyPressed(ImGuiKey_Delete)) ctr_edition->remove_current();

  //----------------------------
}
void Edition::control_keyboard_translation(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  if(io.MouseDown[1]) return;

  //Shift key
  ctr_struct->key_fast = (io.KeysDown[340]) ? true : false;

  // Z key
  if(io.KeysDown[571]) ctr_edition->element_forward();

  // S key
  if(io.KeysDown[564]) ctr_edition->element_backward();

  // D key
  if(io.KeysDown[549]) ctr_edition->element_right();

  // Q key
  if(io.KeysDown[562]) ctr_edition->element_left();

  // A key
  if(io.KeysDown[546]) ctr_edition->element_down();

  // E key
  if(io.KeysDown[550]) ctr_edition->element_up();

  //----------------------------
}
void Edition::control_wheel(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel click - Change mouse wheel mode
  if(ImGui::IsMouseClicked(2)){
    ctr_wheel->change_mode();
  }

  //Wheel actions
  if(!io.MouseDown[1] && io.MouseWheel){
    ctr_wheel->make_action(io.MouseWheel);
  }

  //----------------------------
}

}
