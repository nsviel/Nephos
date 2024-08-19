#include "Navigation.h"

#include <Engine/Control/Namespace.h>
#include <Vulkan/Namespace.h>


namespace ctr::gui{

//Constructor / Destructor
Navigation::Navigation(ctr::Node* node_control){
  //---------------------------

  this->ctr_struct = node_control->get_ctr_struct();
  this->ctr_navigation = node_control->get_ctr_navigation();

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
  ctr_struct->key_fast = (io.KeysDown[340]) ? true : false;

  //Z key or Up key
  if(io.KeysDown[571] || io.KeysDown[515]) ctr_navigation->cam_forward();

  //S key or Down key
  if(io.KeysDown[564] || io.KeysDown[516]) ctr_navigation->cam_backward();

  //Q key or Left key
  if(io.KeysDown[562] || io.KeysDown[513]) ctr_navigation->cam_left();

  //D key or Left key
  if(io.KeysDown[549] || io.KeysDown[514]) ctr_navigation->cam_right();

  //A key
  if(io.KeysDown[546]) ctr_navigation->cam_down();

  //E key
  if(io.KeysDown[550]) ctr_navigation->cam_up();

  //---------------------------
}
void Navigation::control_mouse(){
  //----------------------------

  //Right click - Camera movement
  if(ImGui::IsMouseClicked(1)){
    ctr_navigation->enable_camera_view();
  }

  //Release - back to normal
  else if(ImGui::IsMouseReleased(1)){
    ctr_navigation->disable_camera_view();
  }

  //---------------------------
}
void Navigation::control_wheel(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel + right clicked - Camera zoom
  if(io.MouseDown[1] && io.MouseWheel){
    ctr_navigation->cam_zoom(io.MouseWheel);
  }

  //----------------------------
}


}
