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
  float z_near = camera->clip_near;
  float z_far = camera->clip_far;
  float zoom = camera->zoom;

  // Set a base size for the orthographic projection
  float ortho_size = 10.0f;  // This is a base value, you can adjust as needed
  float zoom_factor = ortho_size + zoom;
  zoom_factor = glm::max(zoom_factor, 0.1f); // Avoid near plane issues

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

  camera->zoom -= value * 0.1;

  //---------------------------
}

}
