#include "Render.h"

#include <Interface/Namespace.h>
#include <Engine/Namespace.h>


namespace ctl::gui{

//Constructor / Destructor
Render::Render(itf::Node* node_interface){
  //---------------------------

  this->itf_struct = node_interface->get_ctl_struct();
  this->node_engine = node_interface->get_node_engine();

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
