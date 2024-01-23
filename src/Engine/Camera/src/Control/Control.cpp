#include "Control.h"


#include <Engine/Engine.h>
#include <Utility/Namespace.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera{

//Constructor / Destructor
Control::Control(Engine* engine){
  //---------------------------

  util::Node* utility = engine->get_utility();
  util::element::Window* utl_window = utility->get_utl_window();

  this->cam_proj = new eng::camera::Projection(utl_window);

  this->vec_mode.push_back(new eng::camera::mode::Player(utl_window));
  this->vec_mode.push_back(new eng::camera::mode::Arcball(utl_window));

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
    case CAMERA_FORWARD:{
      active_mode->camera_forward(camera, cam_speed);
      break;
    }
    case CAMERA_BACKWARD:{
      active_mode->camera_backward(camera, cam_speed);
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
    case CAMERA_UP:{
      active_mode->camera_up(camera, cam_speed);
      break;
    }
    case CAMERA_DOWN:{
      active_mode->camera_down(camera, cam_speed);
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

  active_mode->camera_zoom(camera, value);

  //---------------------------
}

//Camera matrix
mat4 Control::compute_camera_view(){
  mat4 cam_view;
  //---------------------------

  cam_view = active_mode->compute_camera_view(camera);

  //---------------------------
  return cam_view;
}
mat4 Control::compute_camera_proj(){
  mat4 projection;
  //---------------------------

  switch(camera->projection){
    case CAMERA_PROJ_PERSPECTIVE:{
      projection = cam_proj->compute_proj_perspective(camera);
      break;
    }
    case CAMERA_PROJ_ORTHOGRAPHIC:{
      projection = cam_proj->compute_proj_ortho(camera);
      break;
    }
  }

  //---------------------------
  return projection;
}
mat4 Control::compute_camera_mvp(){
  //---------------------------

  mat4 cam_modl = mat4(1);
  mat4 cam_view = compute_camera_view();
  mat4 cam_proj = compute_camera_proj();

  mat4 mvpMatrix = cam_proj * cam_view * cam_modl;

  //---------------------------
  return mvpMatrix;
}
void Control::compute_camera_mvp(utl::type::Pose* pose){
  if(pose == nullptr) return;
  //---------------------------

  mat4 cam_modl = glm::transpose(pose->model);
  mat4 cam_view = compute_camera_view();
  mat4 cam_proj = compute_camera_proj();

  pose->mvp = cam_proj * cam_view * cam_modl;

  //---------------------------
}
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

//Camera parameter
void Control::set_camera(entity::Camera* camera){
  //---------------------------

  this->camera = camera;
  this->set_camera_mode();

  //---------------------------
}
void Control::set_camera_COM(vec3 value){
  //---------------------------

  // Calculate the displacement vector
  vec3 displacement = value - camera->cam_COM;

  // Update the camera position (cam_P) to maintain the same relative position
  camera->cam_P += displacement;

  // Update the camera center (COM)
  camera->cam_COM = value;

  //---------------------------
}
void Control::set_camera_mode(){
  //---------------------------

  switch(camera->mode){
    case CAMERA_MODE_PLAYER:{
      this->active_mode = vec_mode[0];
      break;
    }
    case CAMERA_MODE_ARCBALL:{
      this->active_mode = vec_mode[1];
      break;
    }
  }

  //---------------------------
}
void Control::set_next_camera_mode(){
  //---------------------------

  switch(camera->mode){
    case CAMERA_MODE_PLAYER:{
      camera->reset_entity();
      camera->mode = CAMERA_MODE_ARCBALL;
      break;
    }
    case CAMERA_MODE_ARCBALL:{
      camera->reset_entity();
      camera->mode = CAMERA_MODE_PLAYER;
      break;
    }
  }

  //---------------------------
  this->set_camera_mode();
}


}
