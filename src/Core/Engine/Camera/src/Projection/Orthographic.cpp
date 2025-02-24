#include "Orthographic.h"

#include <Engine/Camera/Namespace.h>
#include <Vulkan/Namespace.h>
#include <glm/gtc/matrix_transform.hpp>


namespace cam::projection{

//Constructor / Destructor
Orthographic::Orthographic(cam::Node* node_camera){
  //---------------------------

  //---------------------------
}
Orthographic::~Orthographic(){}

//Main function
glm::mat4 Orthographic::compute_projection(std::shared_ptr<cam::Entity> camera){
  glm::mat4 cam_proj = glm::mat4(1.0f);
  if(camera == nullptr) return cam_proj;
  //---------------------------

  // Keep near and far clipping planes fixed for depth precision
  float z_near = glm::max(camera->clip_near, 0.01f);
  float z_far = camera->clip_far;

  // Zoom factor adjustment
  float zoom = camera->zoom;
  float ortho_size = 10.0f + zoom; // Dynamically adjust orthographic size
  float zoom_factor = glm::max(ortho_size, 0.1f); // Avoid zero zoom

  // Compute orthographic projection
  cam_proj = glm::ortho(-zoom_factor, zoom_factor, -zoom_factor, zoom_factor, z_near, z_far);

  // Transpose for OpenGL compatibility and flip the Y axis
  cam_proj = glm::transpose(cam_proj);
  cam_proj[1][1] *= -1;  // OpenGL convention for flipped Y axis

  // Save the projection matrix to the camera entity
  camera->mat_proj = cam_proj;

  //---------------------------
  return cam_proj;
}

//Subfunction
void Orthographic::camera_zoom(std::shared_ptr<cam::Entity> camera, float value){
  //---------------------------

  camera->zoom -= value * 0.3;

  //---------------------------
}

}
