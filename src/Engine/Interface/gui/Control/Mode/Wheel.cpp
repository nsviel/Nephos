#include "Wheel.h"

#include <Interface/Namespace.h>


namespace itf::gui{

//Constructor / Destructor
Wheel::Wheel(itf::Node* node_interface){
  //---------------------------

  this->itf_struct = node_interface->get_itf_struct();
  this->itf_wheel = node_interface->get_itf_wheel();

  //---------------------------
}
Wheel::~Wheel(){}

//Main function
void Wheel::run_control(){
  //---------------------------

  this->control_wheel();

  //---------------------------
}

//Subfunction
void Wheel::control_wheel(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel click - Change mouse wheel mode
  if(ImGui::IsMouseClicked(2)){
    itf_wheel->change_mode();
  }

  //Wheel actions
  if(!io.MouseDown[1] && io.MouseWheel){
    //float direction = math::sign(io.MouseWheel);
    //itf_wheel->make_action(direction);
  }

  //----------------------------
}


}
