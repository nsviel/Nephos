#include "Navigation.h"

#include <Interface/Namespace.h>
#include <Camera/Namespace.h>
#include <Vulkan/Namespace.h>


namespace itf::control{

//Constructor / Destructor
Navigation::Navigation(itf::Node* node_interface){
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
Navigation::~Navigation(){}

//Main function
void Navigation::cam_forward(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_FORWARD, itf_struct->control.key_fast);

  //---------------------------
}
void Navigation::cam_backward(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_BACKWARD, itf_struct->control.key_fast);

  //---------------------------
}
void Navigation::cam_left(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_LEFT, itf_struct->control.key_fast);

  //---------------------------
}
void Navigation::cam_right(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_RIGHT, itf_struct->control.key_fast);

  //---------------------------
}
void Navigation::cam_down(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_DOWN, itf_struct->control.key_fast);

  //---------------------------
}
void Navigation::cam_up(){
  //---------------------------

  cam_control->control_keyboard(cam::CAMERA_UP, itf_struct->control.key_fast);

  //---------------------------
}
void Navigation::cam_zoom(float value){
  //---------------------------

  cam_control->control_zoom(value);

  //---------------------------
}

//Subfunction
void Navigation::enable_camera_view(){
  cam::Entity* camera = cam_struct->cam_current;
  //----------------------------

  //Get center of the current panel
  ImVec2 panel_pose = ImGui::GetWindowPos();
  ImVec2 panel_size = ImGui::GetWindowSize();
  int center_x = panel_pose.x + panel_size.x * 0.5f;
  int center_y = panel_pose.y + panel_size.y * 0.5f;
  glm::vec2 center = glm::vec2(center_x, center_y);

  itf_struct->control.cursor_pose = vk_window->get_mouse_pose();

  ImGui::GetIO().MouseDrawCursor = false;
  vk_window->set_mouse_pose(center);
  camera->cam_move = true;
  camera->panel_center = center;

  //----------------------------
}
void Navigation::disable_camera_view(){
  cam::Entity* camera = cam_struct->cam_current;
  //----------------------------

  if(camera->cam_move){
    vk_window->set_mouse_pose(itf_struct->control.cursor_pose);
    camera->cam_move = false;
  }

  //----------------------------
}

}
