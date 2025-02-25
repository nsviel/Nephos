#include "Perspective.h"

#include <Engine/Camera/Namespace.h>
#include <Vulkan/Namespace.h>
#include <glm/gtc/matrix_transform.hpp>


namespace cam::projection{

//Constructor / Destructor
Perspective::Perspective(cam::Node* node_camera){
  //---------------------------

  vk::Node* node_vulkan = node_camera->get_node_vulkan();

  this->vk_window = node_vulkan->get_vk_window();

  //---------------------------
}
Perspective::~Perspective(){}

//Main function
glm::mat4 Perspective::compute_projection(std::shared_ptr<cam::Entity> camera){
  glm::mat4 cam_proj = glm::mat4(1.0f);
  if(camera == nullptr) return cam_proj;
  //---------------------------

  float z_near = camera->clip_near;
  float z_far = camera->clip_far;
  float fov = glm::radians(camera->fov);

  glm::vec2 window_dim = vk_window->get_window_dimension();
  float ratio = window_dim.x / window_dim.y;

  cam_proj = glm::perspective(fov, ratio, z_near, z_far);
  cam_proj[1][1] *= -1;  // This inverts the Y-axis for Vulkan convention

  camera->mat_proj = cam_proj;

  //---------------------------
  return cam_proj;
}

}
