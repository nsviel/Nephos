#include "Edition.h"

#include <Interface/Namespace.h>
#include <Utility/Namespace.h>


namespace ctl::gui{

//Constructor / Destructor
Edition::Edition(itf::Node* node_interface){
  //---------------------------

  this->itf_struct = node_interface->get_itf_struct();
  this->itf_edition = node_interface->get_itf_edition();
  this->itf_wheel = node_interface->get_itf_wheel();

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
  if(ImGui::IsKeyPressed(ImGuiKey_Tab)) itf_edition->select_next();

  //Suppr key - Delete selected
  if(ImGui::IsKeyPressed(ImGuiKey_Delete)) itf_edition->remove_current();

  //----------------------------
}
void Edition::control_keyboard_translation(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  if(io.MouseDown[1]) return;

  //Shift key
  itf_struct->control.key_fast = (io.KeysDown[340]) ? true : false;

  // Z key
  if(io.KeysDown[571]) itf_edition->element_forward();

  // S key
  if(io.KeysDown[564]) itf_edition->element_backward();

  // D key
  if(io.KeysDown[549]) itf_edition->element_right();

  // Q key
  if(io.KeysDown[562]) itf_edition->element_left();

  // A key
  if(io.KeysDown[546]) itf_edition->element_down();

  // E key
  if(io.KeysDown[550]) itf_edition->element_up();

  //----------------------------
}
void Edition::control_wheel(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel click - Change mouse wheel mode
  if(ImGui::IsMouseClicked(2)){
    itf_wheel->change_mode();
  }

  //Wheel actions
  if(!io.MouseDown[1] && io.MouseWheel){
    itf_wheel->make_action(io.MouseWheel);
  }

  //----------------------------
}

}
