#include "Navigation.h"

#include <Engine/Control/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Camera/Namespace.h>


namespace ctr::mode{

//Constructor / Destructor
Navigation::Navigation(ctr::Node* node_control){
  //---------------------------

  cam::Node* node_camera = node_control->get_node_camera();
  vk::Node* node_vulkan = node_camera->get_node_vulkan();

  this->ctr_struct = node_control->get_ctr_struct();
  this->vk_window = node_vulkan->get_vk_window();
  this->cam_struct = node_camera->get_cam_struct();
  this->cam_manager = node_camera->get_cam_manager();
  this->cam_control = node_camera->get_cam_control();

  //---------------------------
}
Navigation::~Navigation(){}

//Main function
void Navigation::cam_forward(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_FORWARD, ctr_struct->key_fast);

  //---------------------------
}
void Navigation::cam_backward(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_BACKWARD, ctr_struct->key_fast);

  //---------------------------
}
void Navigation::cam_left(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_LEFT, ctr_struct->key_fast);

  //---------------------------
}
void Navigation::cam_right(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_RIGHT, ctr_struct->key_fast);

  //---------------------------
}
void Navigation::cam_down(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_DOWN, ctr_struct->key_fast);

  //---------------------------
}
void Navigation::cam_up(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_UP, ctr_struct->key_fast);

  //---------------------------
}
void Navigation::cam_zoom(float value){
  //---------------------------

  cam_control->control_zoom(value);

  //---------------------------
}

//Subfunction
void Navigation::enable_camera_view(){
  std::shared_ptr<cam::Entity> camera = cam_struct->cam_current;
  //----------------------------

  //Get center of the current panel
  ImVec2 panel_pose = ImGui::GetWindowPos();
  ImVec2 panel_size = ImGui::GetWindowSize();
  int center_x = panel_pose.x + panel_size.x * 0.5f;
  int center_y = panel_pose.y + panel_size.y * 0.5f;
  glm::vec2 center = glm::vec2(center_x, center_y);

  ctr_struct->cursor_pose = vk_window->get_mouse_pose();

  ImGui::GetIO().MouseDrawCursor = false;
  vk_window->set_mouse_pose(center);
  camera->cam_move = true;
  camera->panel_center = center;

  //----------------------------
}
void Navigation::disable_camera_view(){
  std::shared_ptr<cam::Entity> camera = cam_struct->cam_current;
  //----------------------------

  if(camera->cam_move){
    vk_window->set_mouse_pose(ctr_struct->cursor_pose);
    camera->cam_move = false;
  }

  //----------------------------
}

}
