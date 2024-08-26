#include "Orthographic.h"

#include <Engine/Camera/Namespace.h>
#include <Vulkan/Namespace.h>
#include <glm/gtc/matrix_transform.hpp>


namespace cam::projection{

//Constructor / Destructor
Orthographic::Orthographic(cam::Node* node_camera){
  //---------------------------

  vk::Node* node_vulkan = node_camera->get_node_vulkan();

  this->vk_window = node_vulkan->get_vk_window();

  //---------------------------
}
Orthographic::~Orthographic(){}

//Main function
glm::mat4 Orthographic::compute_proj_ortho(std::shared_ptr<cam::Entity> camera){
  glm::mat4 cam_proj = glm::mat4(1.0f);
  if(camera == nullptr) return cam_proj;
  //---------------------------

  float z_near = camera->clip_near;
  float z_far = camera->clip_far;
  float zoom = camera->zoom;

  cam_proj = glm::ortho(-5.f - zoom, 5.f + zoom, -5.f - zoom, 5.f + zoom, z_near, z_far);
  cam_proj = glm::transpose(cam_proj); // I dunno why but it's becoming necessary
  cam_proj[1][1] *= -1; // Because glm is designed for OpenGL convention

  camera->mat_proj = cam_proj;

  //---------------------------
  return cam_proj;
}

//Subfunction
void Orthographic::ortho_zoom(std::shared_ptr<cam::Entity> camera, float value){
  //---------------------------

  camera->zoom -= value / 100;

  if(camera->zoom < -4.99) camera->zoom = -4.99;

  //---------------------------
}

}
