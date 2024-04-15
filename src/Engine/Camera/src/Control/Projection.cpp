#include "Projection.h"

#include <Camera/Namespace.h>
#include <Vulkan/Namespace.h>


namespace eng::cam{

//Constructor / Destructor
Projection::Projection(eng::cam::Node* node_camera){
  //---------------------------

  vk::Node* node_vulkan = node_camera->get_node_vulkan();

  this->vk_window = node_vulkan->get_vk_window();

  //---------------------------
}
Projection::~Projection(){}

//Main function
mat4 Projection::compute_proj_perspective(utl::entity::Camera* camera){
  glm::mat4 cam_proj = glm::mat4(1.0f);
  if(camera == nullptr) return cam_proj;
  //---------------------------

  float z_near = camera->clip_near;
  float z_far = camera->clip_far;
  float fov = glm::radians(camera->fov);

  vec2 window_dim = vk_window->update_window_dim();
  float ratio = window_dim.x / window_dim.y;

  cam_proj = perspective(fov, ratio, z_near, z_far);
  cam_proj[1][1] *= -1; // Because glm is designed for OpenGL convention

  camera->mat_proj = cam_proj;

  //---------------------------
  return cam_proj;
}
mat4 Projection::compute_proj_ortho(utl::entity::Camera* camera){
  glm::mat4 cam_proj = glm::mat4(1.0f);
  if(camera == nullptr) return cam_proj;
  //---------------------------

  float z_near = camera->clip_near;
  float z_far = camera->clip_far;
  float zoom = camera->zoom;

  cam_proj = ortho(-5.f - zoom, 5.f + zoom, -5.f - zoom, 5.f + zoom, z_near, z_far);
  cam_proj[1][1] *= -1; // Because glm is designed for OpenGL convention

  camera->mat_proj = cam_proj;

  //---------------------------
  return cam_proj;
}

//Subfunction
void Projection::ortho_zoom(utl::entity::Camera* camera, float value){
  //---------------------------

  camera->zoom -= value / 10;

  //---------------------------
}

}
