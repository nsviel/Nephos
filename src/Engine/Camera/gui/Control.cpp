#include "Control.h"

#include <Engine/Camera/Namespace.h>
#include <Utility/Element/src/Namespace.h>
#include <Utility/Function/Math/fct_math.h>


namespace eng::cam::gui{

//Constructor / Destructor
Control::Control(eng::cam::Node* node_camera){
  //---------------------------

  this->utl_window = node_camera->get_utl_window();
  this->cam_manager = node_camera->get_camera_manager();
  this->cam_control = node_camera->get_camera_control();

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::run_control(){
  //---------------------------

  this->control_keyboard_camMove();
  this->control_mouse();
  this->control_mouse_wheel();

  //---------------------------
}

//Keyboard
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

//Mouse
void Control::control_mouse(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Get center of the current panel
  ImVec2 windowPos = ImGui::GetWindowPos();
  ImVec2 windowSize = ImGui::GetWindowSize();
  int center_x = windowPos.x + windowSize.x * 0.5f;
  int center_y = windowPos.y + windowSize.y * 0.5f;
  ImVec2 center = ImVec2(center_x, center_y);

  utl::entity::Camera* camera = cam_manager->get_current_camera();
  utl_window->set_window_center(vec2(center.x, center.y));

  //Right click - Camera movement
  static vec2 cursorPos;
  if(ImGui::IsMouseClicked(1)){
    cursorPos = utl_window->get_mouse_pose();

    ImGui::GetIO().MouseDrawCursor = false;
    utl_window->set_mouse_pose(vec2(center.x, center.y));
    camera->cam_move = true;
  }
  //Release - back to normal
  if(ImGui::IsMouseReleased(1) && camera->cam_move){
    utl_window->set_mouse_pose(cursorPos);
    camera->cam_move = false;
  }

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

}
