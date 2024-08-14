#include "Render.h"

#include <Control/Namespace.h>
#include <Engine/Namespace.h>
#include <imgui/core/imgui.h>


namespace ctl::gui{

//Constructor / Destructor
Render::Render(ctl::Node* node_control){
  //---------------------------

  this->ctl_struct = node_control->get_ctl_struct();
  this->node_engine = node_control->get_node_engine();

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
    node_engine->close();
  }

  //R key - Reset
  if(ImGui::IsKeyPressed(ImGuiKey_R)){
    node_engine->reset();
  }

  //---------------------------
}


}
