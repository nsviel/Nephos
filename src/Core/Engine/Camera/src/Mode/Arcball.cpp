#include "Arcball.h"

#include <Engine/Camera/Namespace.h>
#include <Vulkan/Namespace.h>
#include <glm/gtc/matrix_transform.hpp>


namespace cam::mode{

//Constructor / Destructor
Arcball::Arcball(cam::Node* node_camera){
  //---------------------------

  vk::Node* node_vulkan = node_camera->get_node_vulkan();

  this->vk_window = node_vulkan->get_vk_window();

  this->origin = glm::vec3(0, 0, 0);

  //---------------------------
}
Arcball::~Arcball(){}

//Camera movement
void Arcball::camera_forward(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  this->displace_camera_COM(camera, glm::vec3(0, speed, 0));

  //---------------------------
}
void Arcball::camera_backward(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  this->displace_camera_COM(camera, glm::vec3(0, -speed, 0));

  //---------------------------
}
void Arcball::camera_right(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  this->displace_camera_COM(camera, glm::vec3(speed, 0, 0));

  //---------------------------
}
void Arcball::camera_left(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  this->displace_camera_COM(camera, glm::vec3(-speed, 0, 0));

  //---------------------------
}
void Arcball::camera_up(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  this->displace_camera_COM(camera, glm::vec3(0, 0, speed));

  //---------------------------
}
void Arcball::camera_down(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  this->displace_camera_COM(camera, glm::vec3(0, 0, -speed));

  //---------------------------
}
void Arcball::camera_mouse(std::shared_ptr<cam::Entity> camera){
  //---------------------------

  glm::vec2 mouse_pose = vk_window->get_mouse_pose();
  glm::vec2 window_dim = vk_window->get_window_dimension();
  glm::vec2 window_center = camera->panel_center;

  // step 1 : Calculate the amount of rotation given the mouse movement.
  float deltaAngleX = (2 * M_PI / window_dim.x); // a movement from left to right = 2*PI = 360 deg
  float deltaAngleY = (M_PI / window_dim.y);  // a movement from top to bottom = PI = 180 deg
  float xAngle = float(window_center.x - mouse_pose.x) * deltaAngleX * camera->arcball_mouse_sensibility.x;
  float yAngle = float(window_center.y - mouse_pose.y) * deltaAngleY * camera->arcball_mouse_sensibility.y;
  glm::vec2 angle = glm::vec2(xAngle, yAngle);

  //Apply movement
  vk_window->set_mouse_pose(window_center);
  this->rotate_by_angle(camera, angle);

  //---------------------------
}
void Arcball::camera_wheel(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  // Calculate the rotation angle around the z-axis
  float lambda = 0.05;
  glm::vec2 angle = glm::vec2(speed * lambda, 0.0f); // Rotation only around the z-axis

  // Apply rotation
  this->rotate_by_angle(camera, angle);

  //---------------------------
}
void Arcball::camera_zoom(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  // Perspective zoom
  glm::vec3 cam_forwardMove = camera->cam_forward * speed * camera->velocity * glm::vec3(0.1, 0.1, 0.1);
  glm::vec3 new_pose = camera->cam_pose + cam_forwardMove;

  // Check if the new pose is within the allowed range
  float min_COM_dist = 0.1;
  if(glm::distance(new_pose, camera->cam_COM) > min_COM_dist){
    camera->cam_pose = new_pose;
  }

  //---------------------------
}

//Subfunction
glm::mat4 Arcball::compute_camera_view(std::shared_ptr<cam::Entity> camera){
  glm::mat4 cam_view = glm::mat4(1.0f);
  if(camera == nullptr) return cam_view;
  //---------------------------

  //Compute camera
  camera->cam_forward = camera->cam_COM - camera->cam_pose;
  camera->cam_up = normalize(cross(camera->cam_right, camera->cam_forward));

  //Compute view matrix
  cam_view = glm::lookAt(camera->cam_pose, camera->cam_COM, camera->cam_up);
  camera->mat_view = cam_view;

  //---------------------------
  return cam_view;
}
void Arcball::rotate_by_angle(std::shared_ptr<cam::Entity> camera, glm::vec2 angle){
  //---------------------------

  // Get the homogeneous position of the camera and pivot point
  glm::vec4 cam_pose(camera->cam_pose.x, camera->cam_pose.y, camera->cam_pose.z, 1);
  glm::vec4 cam_COM(camera->cam_COM.x, camera->cam_COM.y, camera->cam_COM.z, 1);
  glm::vec4 cam_right(camera->cam_right.x, camera->cam_right.y, camera->cam_right.z, 1);

  // step 2: Rotate the camera around the pivot point on the first axis.
  glm::mat4x4 Rz(1.0f);
  Rz = glm::rotate(Rz, angle.x, glm::vec3(0, 0, 1));
  glm::vec4 new_cam_pose = (Rz * (cam_pose - cam_COM)) + cam_COM;
  glm::vec3 new_cam_right = glm::mat3(Rz) * camera->cam_right; // Apply rotation to right vector

  // Step 3: Rotate the camera around the pivot point on the second axis.
  glm::mat4x4 Rr(1.0f);
  Rr = glm::rotate(Rr, angle.y, new_cam_right);
  glm::vec4 final_cam_pose = (Rr * (new_cam_pose - cam_COM)) + cam_COM;

  // Prevent flipping: Check if the new forward vector is too close to a problematic orientation
  glm::vec3 new_cam_forward = glm::normalize(glm::vec3(final_cam_pose - cam_COM));
  if (glm::abs(glm::dot(new_cam_forward, glm::vec3(0, 0, 1))) > 0.99f) {
    // If too close to flipping, cancel the second rotation (Rr) and keep the first rotation (Rz)
    final_cam_pose = new_cam_pose; // Keep the cam pose after first rotation (Rz)
  }

  // Calculate the new camera position without modifying it if the bottom viewport is too close
  if (final_cam_pose.z - camera->clip_near < 0.0f) {
    final_cam_pose.z = camera->clip_near;
  }

  // Update the camera with the valid rotations
  camera->cam_right = new_cam_right;
  camera->cam_pose = glm::vec3(final_cam_pose);

  //---------------------------
}
void Arcball::displace_camera_COM(std::shared_ptr<cam::Entity> camera, const glm::vec3& displacement){
  //---------------------------

  // Extract the camera's forward, right, and up vectors
  glm::vec3 forward = normalize(camera->cam_forward);
  glm::vec3 right = normalize(camera->cam_right);
  glm::vec3 up = normalize(camera->cam_up);

  // Displace camera COM
  glm::vec3 local_displacement = glm::vec3(0);
  local_displacement += displacement.y * forward;
  local_displacement += displacement.x * right;
  local_displacement += displacement.z * glm::vec3(0.0f, 0.0f, 1.0f);

  // Keep the z position constant
  if(displacement.z == 0){
    local_displacement.z = 0.0f;
  }
  glm::vec3 COM_new = camera->cam_COM + local_displacement;

  // Displace camera accordingly
  if(COM_new.z >= 0){
    camera->cam_pose += local_displacement;
    camera->cam_COM = COM_new;
  }

  //---------------------------
}


}
