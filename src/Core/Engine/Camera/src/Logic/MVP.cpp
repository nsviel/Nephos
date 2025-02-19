#include "MVP.h"

#include <Engine/Camera/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace cam{

//Constructor / Destructor
MVP::MVP(cam::Node* node_camera){
  //---------------------------

  vk::Node* node_vulkan = node_camera->get_node_vulkan();

  this->vk_window = node_vulkan->get_vk_window();
  this->cam_struct = node_camera->get_cam_struct();
  this->cam_perspective = new cam::projection::Perspective(node_camera);
  this->cam_ortho = new cam::projection::Orthographic(node_camera);

  //---------------------------
}
MVP::~MVP(){}

//Main function
void MVP::update_mvp(){
  //---------------------------

  //Update vulkan camera matrices
  glm::mat4 cam_view = compute_camera_view();
  glm::mat4 cam_proj = compute_camera_proj();

  vk_window->set_mat_view(cam_view);
  vk_window->set_mat_projection(cam_proj);

  //---------------------------
}

//Subfunction
glm::mat4 MVP::compute_camera_view(){
  std::shared_ptr<cam::Entity> camera = cam_struct->cam_current;
  //---------------------------

  glm::mat4 cam_view = cam_struct->active_mode->compute_camera_view(camera);

  //---------------------------
  return cam_view;
}
glm::mat4 MVP::compute_camera_proj(){
  std::shared_ptr<cam::Entity> camera = cam_struct->cam_current;
  //---------------------------

  glm::mat4 projection = glm::mat4(1.0f);
  if(camera == nullptr) return projection;

  switch(camera->projection){
    case CAMERA_PROJ_PERSPECTIVE:{
      projection = cam_perspective->compute_projection(camera);
      break;
    }
    case CAMERA_PROJ_ORTHOGRAPHIC:{
      projection = cam_ortho->compute_projection(camera);
      break;
    }
  }

  //---------------------------
  return projection;
}
glm::mat4 MVP::compute_camera_mvp(){
  //---------------------------

  glm::mat4 cam_modl = glm::mat4(1);
  glm::mat4 cam_view = compute_camera_view();
  glm::mat4 cam_proj = compute_camera_proj();

  glm::mat4 mvpMatrix = cam_proj * cam_view * cam_modl;

  //---------------------------
  return mvpMatrix;
}
glm::mat4 MVP::compute_camera_pose(){
  std::shared_ptr<cam::Entity> camera = cam_struct->cam_current;
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

}
