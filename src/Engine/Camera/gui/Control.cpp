#include "Control.h"

#include <Camera/Namespace.h>
#include <Vulkan/Namespace.h>


namespace eng::cam::gui{

//Constructor / Destructor
Control::Control(eng::cam::Node* node_camera){
  //---------------------------

  vk::Node* node_vulkan = node_camera->get_node_vulkan();

  this->vk_window = node_vulkan->get_vk_window();
  this->cam_manager = node_camera->get_camera_manager();
  this->cam_control = node_camera->get_camera_control();

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::run_control(vec2 center){
  //---------------------------

  this->control_keyboard_camMove();
  this->control_mouse(center);
  this->control_mouse_wheel();

  //---------------------------
}

//Control
void Control::control_keyboard_camMove(){
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
        cam_control->control_keyboard(CAMERA_FORWARD, is_fast);
      }

      //S key or Down key
      if(io.KeysDown[564] || io.KeysDown[516]){
        cam_control->control_keyboard(CAMERA_BACKWARD, is_fast);
      }

      //Q key or Left key
      if(io.KeysDown[562] || io.KeysDown[513]){
        cam_control->control_keyboard(CAMERA_LEFT, is_fast);
      }

      //D key or Left key
      if(io.KeysDown[549] || io.KeysDown[514]){
        cam_control->control_keyboard(CAMERA_RIGHT, is_fast);
      }

      //A key
      if(io.KeysDown[546]){
        cam_control->control_keyboard(CAMERA_DOWN, is_fast);
      }

      //E key
      if(io.KeysDown[550]){
        cam_control->control_keyboard(CAMERA_UP, is_fast);
      }
    }
  }

  //---------------------------
}
void Control::control_mouse(vec2 center){
  utl::entity::Camera* camera = cam_manager->get_current_camera();
  //----------------------------

  //Right click - Camera movement
  this->enable_camera_view(center);

  //Release - back to normal
  this->disable_camera_view();

  //---------------------------
}
void Control::control_mouse_wheel(){
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
void Control::enable_camera_view(vec2 center){
  utl::entity::Camera* camera = cam_manager->get_current_camera();
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
void Control::disable_camera_view(){
  utl::entity::Camera* camera = cam_manager->get_current_camera();
  //----------------------------

  if(ImGui::IsMouseReleased(1) && camera->cam_move){
    vk_window->set_mouse_pose(cursor_pose);
    camera->cam_move = false;
  }

  //----------------------------
}

}
