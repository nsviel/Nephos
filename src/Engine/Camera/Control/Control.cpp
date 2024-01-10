#include "Control.h"

#include <Engine/Base/Namespace.h>
#include <Engine/Engine.h>
#include <Utility/Namespace.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera{

//Constructor / Destructor
Control::Control(Engine* engine, eng::data::Camera* camera){
  //---------------------------

  util::Node* utility = engine->get_utility();
  util::element::Window* utl_window = utility->get_utl_window();

  this->cam_zoom = new eng::camera::Zoom(utl_window);

  this->vec_mode.push_back(new eng::camera::mode::Player(utl_window));
  this->vec_mode.push_back(new eng::camera::mode::Arcball(utl_window));
  this->active_mode = vec_mode[0];
  this->camera = camera;

  //---------------------------
}
Control::~Control(){}

//Camera movement
void Control::control_keyboard(int direction, bool fast){
  //---------------------------

  //Compute camera movment speed value
  float cam_speed = camera->speed_move * 0.000016;
  if(fast){
    cam_speed *= 5;
  }

  switch(direction){
    case CAMERA_UP:{
      active_mode->camera_up(camera, cam_speed);
      break;
    }
    case CAMERA_DOWN:{
      active_mode->camera_down(camera, cam_speed);
      break;
    }
    case CAMERA_RIGHT:{
      active_mode->camera_right(camera, cam_speed);
      break;
    }
    case CAMERA_LEFT:{
      active_mode->camera_left(camera, cam_speed);
      break;
    }
  }

  //---------------------------
}
void Control::control_mouse(){
  //---------------------------

  if(camera->cam_move){
    active_mode->camera_mouse(camera);
    ImGui::SetMouseCursor(ImGuiMouseCursor_None);
  }

  //---------------------------
}
void Control::control_zoom(float value){
  //---------------------------

  cam_zoom->compute_zoom_position(camera, value);

  //---------------------------
}

//Camera matrix
mat4 Control::compute_camera_pose(){
  //---------------------------

  vec3 zaxis = normalize(camera->cam_F);
  vec3 xaxis = normalize(cross(camera->cam_U, zaxis));
  vec3 yaxis = cross(zaxis, xaxis);

  mat4 absPose(
    xaxis[0], yaxis[0], zaxis[0], camera->cam_P[0],
    xaxis[1], yaxis[1], zaxis[1], camera->cam_P[1],
    xaxis[2], yaxis[2], zaxis[2], camera->cam_P[2],
    0,       0,       0,     1);

  //---------------------------
  return absPose;
}


}
