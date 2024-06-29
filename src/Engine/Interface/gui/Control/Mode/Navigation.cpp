#include "Navigation.h"

#include <Interface/Namespace.h>
#include <Camera/Namespace.h>
#include <Vulkan/Namespace.h>


namespace itf::gui{

//Constructor / Destructor
Navigation::Navigation(itf::Node* node_interface){
  //---------------------------

  this->itf_struct = node_interface->get_itf_struct();
  this->itf_camera = node_interface->get_itf_camera();

  //---------------------------
}
Navigation::~Navigation(){}

//Main function
void Navigation::run_control(glm::vec2 center){
  //---------------------------

  this->control_keyboard();
  this->control_mouse(center);
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
  if(io.KeysDown[571] || io.KeysDown[515]) itf_camera->cam_forward();

  //S key or Down key
  if(io.KeysDown[564] || io.KeysDown[516]) itf_camera->cam_backward();

  //Q key or Left key
  if(io.KeysDown[562] || io.KeysDown[513]) itf_camera->cam_left();

  //D key or Left key
  if(io.KeysDown[549] || io.KeysDown[514]) itf_camera->cam_right();

  //A key
  if(io.KeysDown[546]) itf_camera->cam_down();

  //E key
  if(io.KeysDown[550]) itf_camera->cam_up();

  //---------------------------
}
void Navigation::control_mouse(glm::vec2 center){
  //----------------------------

  //Right click - Camera movement
  if(ImGui::IsMouseClicked(1)){
    itf_camera->enable_camera_view(center);
  }

  //Release - back to normal
  else if(ImGui::IsMouseReleased(1)){
    itf_camera->disable_camera_view();
  }

  //---------------------------
}
void Navigation::control_wheel(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel + right clicked - Camera zoom
  if(io.MouseDown[1] && io.MouseWheel){
    itf_camera->cam_zoom(io.MouseWheel);
  }

  //----------------------------
}


}
