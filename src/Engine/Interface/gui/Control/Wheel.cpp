#include "Element.h"

#include <Engine/Namespace.h>
#include <Utility/Namespace.h>
#include <Data/Namespace.h>
#include <Interface/Namespace.h>
#include <Operation/Namespace.h>
#include <glm/glm.hpp>


namespace itf::gui{

//Constructor / Destructor
Element::Element(itf::Node* node_interface){
  //---------------------------

  this->itf_struct = node_interface->get_itf_struct();
  this->itf_wheel = node_interface->get_itf_wheel();

  //---------------------------
}
Element::~Element(){}

//Main function
void Element::run_control(){
  //---------------------------

  this->control_wheel();

  //---------------------------
}

//Subfunction
void Element::control_wheel(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel click - Change mouse wheel mode
  if(ImGui::IsMouseClicked(2)){
    itf_wheel->change_mode();
  }

  //Wheel actions
  if(!io.MouseDown[1] && io.MouseWheel){
    float direction = math::sign(io.MouseWheel);
    itf_wheel->make_action(direction);
  }

  //----------------------------
}


}
