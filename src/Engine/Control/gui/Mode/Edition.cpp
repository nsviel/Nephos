#include "Edition.h"

#include <Interface/Namespace.h>
#include <Utility/Namespace.h>


namespace ctl::gui{

//Constructor / Destructor
Edition::Edition(ctl::Node* node_control){
  //---------------------------

  this->ctl_struct = node_control->get_ctl_struct();
  this->ctl_edition = node_control->get_ctl_edition();
  this->ctl_wheel = node_control->get_ctl_wheel();

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
  if(ImGui::IsKeyPressed(ImGuiKey_Tab)) ctl_edition->select_next();

  //Suppr key - Delete selected
  if(ImGui::IsKeyPressed(ImGuiKey_Delete)) ctl_edition->remove_current();

  //----------------------------
}
void Edition::control_keyboard_translation(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  if(io.MouseDown[1]) return;

  //Shift key
  ctl_struct->control.key_fast = (io.KeysDown[340]) ? true : false;

  // Z key
  if(io.KeysDown[571]) ctl_edition->element_forward();

  // S key
  if(io.KeysDown[564]) ctl_edition->element_backward();

  // D key
  if(io.KeysDown[549]) ctl_edition->element_right();

  // Q key
  if(io.KeysDown[562]) ctl_edition->element_left();

  // A key
  if(io.KeysDown[546]) ctl_edition->element_down();

  // E key
  if(io.KeysDown[550]) ctl_edition->element_up();

  //----------------------------
}
void Edition::control_wheel(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel click - Change mouse wheel mode
  if(ImGui::IsMouseClicked(2)){
    ctl_wheel->change_mode();
  }

  //Wheel actions
  if(!io.MouseDown[1] && io.MouseWheel){
    ctl_wheel->make_action(io.MouseWheel);
  }

  //----------------------------
}

}
