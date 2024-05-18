#include "Control.h"

#include <Camera/Namespace.h>
#include <Utility/Namespace.h>


namespace cam{

//Constructor / Destructor
Control::Control(cam::Node* node_camera){
  //---------------------------

  this->cam_struct = node_camera->get_cam_struct();
  this->cam_proj = new cam::Projection(node_camera);

  this->vec_mode.push_back(new cam::mode::Player(node_camera));
  this->vec_mode.push_back(new cam::mode::Arcball(node_camera));
  this->active_mode = vec_mode[0];

  //---------------------------
}
Control::~Control(){}

//Camera movement
void Control::control_keyboard(int direction, bool fast){
  cam::Entity* camera = cam_struct->cam_current;
  //---------------------------

  //Compute camera movment speed value
  float cam_speed = camera->velocity * 0.000016;
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
  cam::Entity* camera = cam_struct->cam_current;
  //---------------------------

  if(camera->cam_move){
    active_mode->camera_mouse(camera);
    ImGui::SetMouseCursor(ImGuiMouseCursor_None);
  }

  //---------------------------
}
void Control::control_zoom(float value){
  cam::Entity* camera = cam_struct->cam_current;
  //---------------------------

  switch(camera->projection){
    case CAMERA_PROJ_PERSPECTIVE:{
      active_mode->camera_zoom(camera, value);
      break;
    }
    case CAMERA_PROJ_ORTHOGRAPHIC:{
      cam_proj->ortho_zoom(camera, value);
      break;
    }
  }

  //---------------------------
}
void Control::control_wheel(float value){
  cam::Entity* camera = cam_struct->cam_current;
  //---------------------------

  active_mode->camera_wheel(camera, value);

  //---------------------------
}

//Camera matrix
glm::mat4 Control::compute_camera_view(){
  cam::Entity* camera = cam_struct->cam_current;
  //---------------------------

  glm::mat4 cam_view = active_mode->compute_camera_view(camera);

  //---------------------------
  return cam_view;
}
glm::mat4 Control::compute_camera_proj(){
  cam::Entity* camera = cam_struct->cam_current;
  //---------------------------

  glm::mat4 projection = glm::mat4(1.0f);
  if(camera == nullptr) return projection;

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
glm::mat4 Control::compute_camera_mvp(){
  //---------------------------

  glm::mat4 cam_modl = glm::mat4(1);
  glm::mat4 cam_view = compute_camera_view();
  glm::mat4 cam_proj = compute_camera_proj();

  glm::mat4 mvpMatrix = cam_proj * cam_view * cam_modl;

  //---------------------------
  return mvpMatrix;
}
void Control::compute_camera_mvp(utl::base::Pose* pose){
  if(pose == nullptr) return;
  //---------------------------

  glm::mat4 cam_modl = glm::transpose(pose->model);
  glm::mat4 cam_view = compute_camera_view();
  glm::mat4 cam_proj = compute_camera_proj();

  pose->mvp = cam_proj * cam_view * cam_modl;

  //---------------------------
}
glm::mat4 Control::compute_camera_pose(){
  cam::Entity* camera = cam_struct->cam_current;
  //---------------------------

  glm::vec3 zaxis = normalize(camera->cam_F);
  glm::vec3 xaxis = normalize(cross(camera->cam_U, zaxis));
  glm::vec3 yaxis = cross(zaxis, xaxis);

  glm::mat4 absPose(
    xaxis[0], yaxis[0], zaxis[0], camera->cam_P[0],
    xaxis[1], yaxis[1], zaxis[1], camera->cam_P[1],
    xaxis[2], yaxis[2], zaxis[2], camera->cam_P[2],
    0,       0,       0,     1);

  //---------------------------
  return absPose;
}

//Camera parameter
void Control::set_camera_COM(glm::vec3 value){
  cam::Entity* camera = cam_struct->cam_current;
  //---------------------------

  // Calculate the displacement vector
  glm::vec3 displacement = value - camera->cam_COM;

  // Update the camera position (cam_P) to maintain the same relative position
  camera->cam_P += displacement;

  // Update the camera center (COM)
  camera->cam_COM = value;

  //---------------------------
}
void Control::set_camera_mode(cam::Entity* camera){
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
void Control::set_camera_proj(cam::Entity* camera, int projection){
  //---------------------------

  switch(projection){
    case CAMERA_PROJ_PERSPECTIVE:{
      camera->reset();
      camera->projection = projection;
      break;
    }
    case CAMERA_PROJ_ORTHOGRAPHIC:{
      camera->reset();
      camera->projection = projection;
      camera->cam_P = glm::vec3(-20, -20, 10);
      camera->clip_far = 1000.0;
      break;
    }
  }

  //---------------------------
}
void Control::set_next_camera_mode(){
  cam::Entity* camera = cam_struct->cam_current;
  //---------------------------

  switch(camera->mode){
    case CAMERA_MODE_PLAYER:{
      camera->reset();
      camera->mode = CAMERA_MODE_ARCBALL;
      break;
    }
    case CAMERA_MODE_ARCBALL:{
      camera->reset();
      camera->mode = CAMERA_MODE_PLAYER;
      break;
    }
  }

  //---------------------------
  this->set_camera_mode(camera);
}


}
