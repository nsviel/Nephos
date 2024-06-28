#include "Camera.h"

#include <Interface/Namespace.h>
#include <Camera/Namespace.h>
#include <Vulkan/Namespace.h>


namespace itf::control{

//Constructor / Destructor
Camera::Camera(itf::Node* node_interface){
  //---------------------------

  cam::Node* node_camera = node_interface->get_node_camera();
  vk::Node* node_vulkan = node_camera->get_node_vulkan();

  this->itf_struct = node_interface->get_itf_struct();
  this->vk_window = node_vulkan->get_vk_window();
  this->cam_struct = node_camera->get_cam_struct();
  this->cam_manager = node_camera->get_cam_manager();
  this->cam_control = node_camera->get_cam_control();

  //---------------------------
}
Camera::~Camera(){}

//Main function
void Camera::cam_forward(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_FORWARD, itf_struct->control.cam_fast);

  //---------------------------
}
void Camera::cam_backward(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_BACKWARD, itf_struct->control.cam_fast);

  //---------------------------
}
void Camera::cam_left(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_LEFT, itf_struct->control.cam_fast);

  //---------------------------
}
void Camera::cam_right(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_RIGHT, itf_struct->control.cam_fast);

  //---------------------------
}
void Camera::cam_down(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_DOWN, itf_struct->control.cam_fast);

  //---------------------------
}
void Camera::cam_up(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_UP, itf_struct->control.cam_fast);

  //---------------------------
}
void Camera::cam_zoom(float value){
  //---------------------------

  cam_control->control_zoom(value);

  //---------------------------
}

//Subfunction
void Camera::enable_camera_view(glm::vec2 center){
  cam::Entity* camera = cam_struct->cam_current;
  //----------------------------

  itf_struct->control.cursor_pose = vk_window->get_mouse_pose();

  ImGui::GetIO().MouseDrawCursor = false;
  vk_window->set_mouse_pose(center);
  camera->cam_move = true;
  camera->panel_center = center;

  //----------------------------
}
void Camera::disable_camera_view(){
  cam::Entity* camera = cam_struct->cam_current;
  //----------------------------

  if(camera->cam_move){
    vk_window->set_mouse_pose(itf_struct->control.cursor_pose);
    camera->cam_move = false;
  }

  //----------------------------
}

}
