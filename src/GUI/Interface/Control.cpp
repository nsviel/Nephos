#include "Control.h"

#include <GUI/Namespace.h>
#include <Engine/Namespace.h>
#include <Vulkan/Namespace.h>


namespace gui::interface{

//Constructor / Destructor
Control::Control(gui::Node* node_gui){
  //---------------------------

  vk::Node* node_vulkan = node_gui->get_node_vulkan();

  this->vk_window = node_vulkan->get_vk_window();
  this->node_tab = node_gui->get_node_tab();

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::run_control(){
  //---------------------------

  this->control_keyboard_oneAction();

  //---------------------------
}

//Keyboard
void Control::control_keyboard_oneAction(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    //Esc key - Close program
    if(ImGui::IsKeyPressed(ImGuiKey_Escape)){
      vk_window->close_window();
    }

    //1 key - Next main tab
    if(ImGui::IsKeyPressed(ImGuiKey_LeftAlt)){
      node_tab->next_tab();
    }
  }

  //----------------------------
}

//Mouse

}
