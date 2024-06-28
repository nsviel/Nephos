#include "Camera.h"

#include <Camera/Namespace.h>
#include <Vulkan/Namespace.h>


namespace itf::gui{

//Constructor / Destructor
Camera::Camera(cam::Node* node_camera){
  //---------------------------

  vk::Node* node_vulkan = node_camera->get_node_vulkan();

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
      bool is_fast = false;
      if(io.KeysDown[340]){
        is_fast = true;
      }

      //Z key or Up key
      if(io.KeysDown[571] || io.KeysDown[515]){
        cam_control->control_keyboard(cam::CAMERA_FORWARD, is_fast);
      }

      //S key or Down key
      if(io.KeysDown[564] || io.KeysDown[516]){
        cam_control->control_keyboard(cam::CAMERA_BACKWARD, is_fast);
      }

      //Q key or Left key
      if(io.KeysDown[562] || io.KeysDown[513]){
        cam_control->control_keyboard(cam::CAMERA_LEFT, is_fast);
      }

      //D key or Left key
      if(io.KeysDown[549] || io.KeysDown[514]){
        cam_control->control_keyboard(cam::CAMERA_RIGHT, is_fast);
      }

      //A key
      if(io.KeysDown[546]){
        cam_control->control_keyboard(cam::CAMERA_DOWN, is_fast);
      }

      //E key
      if(io.KeysDown[550]){
        cam_control->control_keyboard(cam::CAMERA_UP, is_fast);
      }
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
