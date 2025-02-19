#include "Control.h"

#include <Engine/Camera/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace cam{

//Constructor / Destructor
Control::Control(cam::Node* node_camera){
  //---------------------------

  vk::Node* node_vulkan = node_camera->get_node_vulkan();

  this->vk_window = node_vulkan->get_vk_window();
  this->cam_struct = node_camera->get_cam_struct();
  this->cam_perspective = new cam::projection::Perspective(node_camera);
  this->cam_ortho = new cam::projection::Orthographic(node_camera);

  cam_struct->vec_mode.push_back(new cam::mode::Player(node_camera));
  cam_struct->vec_mode.push_back(new cam::mode::Arcball(node_camera));
  cam_struct->active_mode = cam_struct->vec_mode[0];

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::control_keyboard(int direction, bool fast){
  std::shared_ptr<cam::Entity> camera = cam_struct->cam_current;
  //---------------------------

  //Compute camera movment speed value
  float cam_speed = camera->velocity * 0.01;
  if(fast){
    cam_speed *= 5;
  }

  switch(direction){
    case CAMERA_FORWARD:{
      cam_struct->active_mode->camera_forward(camera, cam_speed);
      break;
    }
    case CAMERA_BACKWARD:{
      cam_struct->active_mode->camera_backward(camera, cam_speed);
      break;
    }
    case CAMERA_RIGHT:{
      cam_struct->active_mode->camera_right(camera, cam_speed);
      break;
    }
    case CAMERA_LEFT:{
      cam_struct->active_mode->camera_left(camera, cam_speed);
      break;
    }
    case CAMERA_UP:{
      cam_struct->active_mode->camera_up(camera, cam_speed);
      break;
    }
    case CAMERA_DOWN:{
      cam_struct->active_mode->camera_down(camera, cam_speed);
      break;
    }
  }

  //---------------------------
}
void Control::control_mouse(){
  std::shared_ptr<cam::Entity> camera = cam_struct->cam_current;
  //---------------------------

  if(camera->cam_move){
    cam_struct->active_mode->camera_mouse(camera);
    ImGui::SetMouseCursor(ImGuiMouseCursor_None);
  }

  //---------------------------
}
void Control::control_zoom(float value){
  std::shared_ptr<cam::Entity> camera = cam_struct->cam_current;
  //---------------------------

  switch(camera->projection){
    case CAMERA_PROJ_PERSPECTIVE:{
      cam_struct->active_mode->camera_zoom(camera, value);
      break;
    }
    case CAMERA_PROJ_ORTHOGRAPHIC:{
      cam_ortho->camera_zoom(camera, value);
      break;
    }
  }

  //---------------------------
}
void Control::control_wheel(float value){
  std::shared_ptr<cam::Entity> camera = cam_struct->cam_current;
  //---------------------------

  cam_struct->active_mode->camera_wheel(camera, value);

  //---------------------------
}

//Camera parameter
void Control::set_camera_COM(glm::vec3 value){
  std::shared_ptr<cam::Entity> camera = cam_struct->cam_current;
  //---------------------------

  // Calculate the displacement vector
  glm::vec3 displacement = value - camera->cam_COM;

  // Update the camera position (cam_P) to maintain the same relative position
  camera->cam_P += displacement;

  // Update the camera center (COM)
  camera->cam_COM = value;

  //---------------------------
}
void Control::set_camera_mode(std::shared_ptr<cam::Entity> camera){
  //---------------------------

  switch(camera->mode){
    case CAMERA_MODE_PLAYER:{
      cam_struct->active_mode = cam_struct->vec_mode[0];
      break;
    }
    case CAMERA_MODE_ARCBALL:{
      cam_struct->active_mode = cam_struct->vec_mode[1];
      break;
    }
  }

  //---------------------------
}
void Control::set_camera_proj(std::shared_ptr<cam::Entity> camera, int projection){
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
  std::shared_ptr<cam::Entity> camera = cam_struct->cam_current;
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
