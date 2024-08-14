#include "Render.h"

#include <Control/Namespace.h>
#include <Core/Namespace.h>
#include <imgui/core/imgui.h>


namespace ctr::gui{

//Constructor / Destructor
Render::Render(ctr::Node* node_control){
  //---------------------------

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
    node_core->close();
  }

  //R key - Reset
  if(ImGui::IsKeyPressed(ImGuiKey_R)){
    node_core->reset();
  }

  //---------------------------
}


}
