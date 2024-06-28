#include "Camera.h"

#include <Interface/Namespace.h>
#include <Camera/Namespace.h>
#include <Vulkan/Namespace.h>


namespace itf::gui{

//Constructor / Destructor
Camera::Camera(itf::Node* node_interface){
  //---------------------------

  cam::Node* node_camera = node_interface->get_node_camera();
  vk::Node* node_vulkan = node_interface->get_node_vulkan();

  this->itf_struct = node_interface->get_itf_struct();
  this->itf_camera = node_interface->get_itf_camera();
  this->vk_window = node_vulkan->get_vk_window();
  this->cam_struct = node_camera->get_cam_struct();
  this->cam_manager = node_camera->get_cam_manager();
  this->cam_control = node_camera->get_cam_control();

  //---------------------------
}
Camera::~Camera(){}

//Main function
void Camera::run_control(glm::vec2 center){
  //---------------------------

  this->control_keyboard_camMove();
  this->control_mouse(center);
  this->control_mouse_wheel();

  //---------------------------
}

//Control
void Camera::control_keyboard_camMove(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    if(io.MouseDown[1]){

      //Shift speed up
      itf_struct->control.cam_fast = (io.KeysDown[340]) ? true : false;

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
    }
  }

  //---------------------------
}
void Camera::control_mouse(glm::vec2 center){
  cam::Entity* camera = cam_struct->cam_current;
  //----------------------------

  //Right click - Camera movement
  this->enable_camera_view(center);

  //Release - back to normal
  this->disable_camera_view();

  //---------------------------
}
void Camera::control_mouse_wheel(){
  static int wheel_mode = 0;
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel + right clicked - Camera zoom
  if(io.MouseWheel && io.MouseDownDuration[1] >= 0.0f){
    cam_control->control_zoom(io.MouseWheel);
  }

  //----------------------------
}

//Subfunction
void Camera::enable_camera_view(glm::vec2 center){
  cam::Entity* camera = cam_struct->cam_current;
  //----------------------------

  if(ImGui::IsMouseClicked(1)){
    cursor_pose = vk_window->get_mouse_pose();

    ImGui::GetIO().MouseDrawCursor = false;
    vk_window->set_mouse_pose(center);
    camera->cam_move = true;
    camera->panel_center = center;
  }

  //----------------------------
}
void Camera::disable_camera_view(){
  cam::Entity* camera = cam_struct->cam_current;
  //----------------------------

  if(ImGui::IsMouseReleased(1) && camera->cam_move){
    vk_window->set_mouse_pose(cursor_pose);
    camera->cam_move = false;
  }

  //----------------------------
}

}
