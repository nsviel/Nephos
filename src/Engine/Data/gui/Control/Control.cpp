#include "Control.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#include <Render/Namespace.h>
#include <Operation/Namespace.h>
#include <glm/glm.hpp>


namespace dat::gui{

//Constructor / Destructor
Control::Control(dat::Node* node_data){
  //---------------------------

  this->dat_selection = node_data->get_dat_selection();
  this->dat_set = node_data->get_dat_set();
  this->ope_operation = new ope::Operation();
  this->gui_wheel = node_data->get_gui_wheel();

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::run_control(){
  //---------------------------

  this->control_keyboard_oneAction();
  this->control_keyboard_translation();
  this->control_mouse_wheel();

  //---------------------------
}

//Keyboard
void Control::control_keyboard_oneAction(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    //Tab key
    if(ImGui::IsKeyPressed(ImGuiKey_Tab)){
      dat_selection->select_next_element();
      break;
    }

    //Suppr key - Delete selected
    if(ImGui::IsKeyPressed(ImGuiKey_Delete)){
      dat::base::Set* set = dat_selection->get_selected_set();
      dat_set->remove_entity(set, set->active_entity);
      break;
    }
  }

  //----------------------------
}
void Control::control_keyboard_translation(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++){
    if(!io.MouseDown[1]){
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
        break;
      }
      // S key
      if(io.KeysDown[564]){
        glm::vec3 translation = glm::vec3(-translation_qtt, 0, 0);
        ope_operation->make_translation(element, translation);
        break;
      }
      // D key
      if(io.KeysDown[549]){
        glm::vec3 translation = glm::vec3(0, translation_qtt, 0);
        ope_operation->make_translation(element, translation);
        break;
      }
      // Q key
      if(io.KeysDown[562]){
        glm::vec3 translation = glm::vec3(0, -translation_qtt, 0);
        ope_operation->make_translation(element, translation);
        break;
      }
      // A key
      if(io.KeysDown[546]){
        glm::vec3 translation = glm::vec3(0, 0, translation_qtt);
        ope_operation->make_translation(element, translation);
        break;
      }
      // E key
      if(io.KeysDown[550]){
        glm::vec3 translation = glm::vec3(0, 0, -translation_qtt);
        ope_operation->make_translation(element, translation);
        break;
      }
    }
  }

  //----------------------------
}

//Mouse
void Control::control_mouse_wheel(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel click - Change mouse wheel mode
  if(ImGui::IsMouseClicked(2)){
    gui_wheel->change_mode();
  }

  //Wheel actions
  if(io.MouseWheel && io.MouseDownDuration[1] == -1){
    float direction = math::sign(io.MouseWheel);
    gui_wheel->make_action(direction);
  }

  //----------------------------
}


}
