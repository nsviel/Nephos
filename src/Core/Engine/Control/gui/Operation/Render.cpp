#include "Render.h"

#include <Engine/Control/Namespace.h>
#include <imgui/core/imgui.h>


namespace ctr::gui{

//Constructor / Destructor
Render::Render(ctr::Node* node_control){
  //---------------------------

  this->node_control = node_control;
  this->ctr_struct = node_control->get_ctr_struct();
  this->node_core = node_control->get_node_core();

  //---------------------------
}
Render::~Render(){}

//Main function
void Render::run_control(){
  //---------------------------

  this->control_keyboard();

  //---------------------------
}

//Keyboard
void Render::control_keyboard(){
  //----------------------------

  //Esc key - Close program
  if(ImGui::IsKeyPressed(ImGuiKey_Escape)){
    node_control->close();
  }

  //R key - Reset
  if(ImGui::IsKeyPressed(ImGuiKey_R)){
    node_control->reset();
  }

  //---------------------------
}


}
