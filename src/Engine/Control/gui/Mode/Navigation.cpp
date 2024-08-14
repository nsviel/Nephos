#include "Navigation.h"

#include <Interface/Namespace.h>
#include <Camera/Namespace.h>
#include <Vulkan/Namespace.h>


namespace ctl::gui{

//Constructor / Destructor
Navigation::Navigation(itf::Node* node_interface){
  //---------------------------

  this->itf_struct = node_interface->get_ctl_struct();
  this->ctl_navigation = node_interface->get_ctl_navigation();

  //---------------------------
}
Navigation::~Navigation(){}

//Main function
void Navigation::run_control(){
  //---------------------------

  this->control_keyboard();
  this->control_mouse();
  this->control_wheel();

  //---------------------------
}

//Subfunction
void Navigation::control_keyboard(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  if(!io.MouseDown[1]) return;

  //Shift speed up
  itf_struct->control.key_fast = (io.KeysDown[340]) ? true : false;

  //Z key or Up key
  if(io.KeysDown[571] || io.KeysDown[515]) ctl_navigation->cam_forward();

  //S key or Down key
  if(io.KeysDown[564] || io.KeysDown[516]) ctl_navigation->cam_backward();

  //Q key or Left key
  if(io.KeysDown[562] || io.KeysDown[513]) ctl_navigation->cam_left();

  //D key or Left key
  if(io.KeysDown[549] || io.KeysDown[514]) ctl_navigation->cam_right();

  //A key
  if(io.KeysDown[546]) ctl_navigation->cam_down();

  //E key
  if(io.KeysDown[550]) ctl_navigation->cam_up();

  //---------------------------
}
void Navigation::control_mouse(){
  //----------------------------

  //Right click - Camera movement
  if(ImGui::IsMouseClicked(1)){
    ctl_navigation->enable_camera_view();
  }

  //Release - back to normal
  else if(ImGui::IsMouseReleased(1)){
    ctl_navigation->disable_camera_view();
  }

  //---------------------------
}
void Navigation::control_wheel(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel + right clicked - Camera zoom
  if(io.MouseDown[1] && io.MouseWheel){
    ctl_navigation->cam_zoom(io.MouseWheel);
  }

  //----------------------------
}


}
