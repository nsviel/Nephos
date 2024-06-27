#include "Arcball.h"

#include <Camera/Namespace.h>
#include <Vulkan/Namespace.h>


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
void Arcball::camera_forward(cam::Entity* camera, float speed){
  //---------------------------

  this->displace_camera_COM(camera, glm::vec3(0, speed, 0));

  //---------------------------
}
void Arcball::camera_backward(cam::Entity* camera, float speed){
  //---------------------------

  this->displace_camera_COM(camera, glm::vec3(0, -speed, 0));

  //---------------------------
}
void Arcball::camera_right(cam::Entity* camera, float speed){
  //---------------------------

  this->displace_camera_COM(camera, glm::vec3(speed, 0, 0));

  //---------------------------
}
void Arcball::camera_left(cam::Entity* camera, float speed){
  //---------------------------

  this->displace_camera_COM(camera, glm::vec3(-speed, 0, 0));

  //---------------------------
}
void Arcball::camera_up(cam::Entity* camera, float speed){
  //---------------------------

  this->displace_camera_COM(camera, glm::vec3(0, 0, speed));

  //---------------------------
}
void Arcball::camera_down(cam::Entity* camera, float speed){
  //---------------------------

  this->displace_camera_COM(camera, glm::vec3(0, 0, -speed));

  //---------------------------
}
void Arcball::camera_mouse(cam::Entity* camera){
  //---------------------------

  glm::vec2 mouse_pose = vk_window->get_mouse_pose();
  glm::vec2 window_dim = vk_window->get_dimension();
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
void Arcball::camera_wheel(cam::Entity* camera, float speed){
  //---------------------------

  // Calculate the rotation angle around the z-axis
  float lambda = 0.05;
  glm::vec2 angle = glm::vec2(speed * lambda, 0.0f); // Rotation only around the z-axis

  // Apply rotation
  this->rotate_by_angle(camera, angle);

  //---------------------------
}
void Arcball::camera_zoom(cam::Entity* camera, float speed){
  //---------------------------

  // Perspective zoom
  glm::vec3 cam_forwardMove = camera->cam_F * speed * camera->velocity * glm::vec3(0.1, 0.1, 0.1);
  glm::vec3 new_pose = camera->cam_P + cam_forwardMove;

  // Check if the new pose is within the allowed range
  float min_COM_dist = 0.1;
  if(glm::distance(new_pose, camera->cam_COM) > min_COM_dist){
    camera->cam_P = new_pose;
  }

  //---------------------------
}

//Subfunction
mat4 Arcball::compute_camera_view(cam::Entity* camera){
  glm::mat4 cam_view = glm::mat4(1.0f);
  if(camera == nullptr) return cam_view;
  //---------------------------

  //Compute camera
  camera->cam_F = camera->cam_COM - camera->cam_P;
  camera->cam_U = normalize(cross(camera->cam_R, camera->cam_F));

  //Compute view matrix
  cam_view = lookAt(camera->cam_P, camera->cam_COM, camera->cam_U);

  //---------------------------
  return cam_view;
}
void Arcball::rotate_by_angle(cam::Entity* camera, glm::vec2 angle){
  //---------------------------

  // Get the homogenous position of the camera and pivot point
  glm::vec4 cam_P(camera->cam_P.x, camera->cam_P.y, camera->cam_P.z, 1);
  glm::vec4 cam_COM(camera->cam_COM.x, camera->cam_COM.y, camera->cam_COM.z, 1);
  glm::vec4 cam_R(camera->cam_R.x, camera->cam_R.y, camera->cam_R.z, 1);

  // step 2: Rotate the camera around the pivot point on the first axis.
  glm::mat4x4 Rz(1.0f);
  Rz = glm::rotate(Rz, angle.x, glm::vec3(0, 0, 1));
  cam_P = (Rz * (cam_P - cam_COM)) + cam_COM;
  camera->cam_R = Rz * cam_R;

  // Step 3: Rotate the camera around the pivot point on the second axis.
  glm::mat4x4 Rr(1.0f);
  Rr = glm::rotate(Rr, angle.y, camera->cam_R);
  cam_P = (Rr * (cam_P - cam_COM)) + cam_COM;

  // Calculate the new camera position without modifying it if the bottom viewport is too close
  if(cam_P.z - camera->clip_near < 0.0f){
    cam_P.z = camera->clip_near;
  }

  camera->cam_P = cam_P;

  //---------------------------
}
void Arcball::displace_camera_COM(cam::Entity* camera, const glm::vec3& displacement){
  //---------------------------

  // Extract the camera's forward, right, and up vectors
  glm::vec3 forward = normalize(camera->cam_F);
  glm::vec3 right = normalize(camera->cam_R);
  glm::vec3 up = normalize(camera->cam_U);

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
    camera->cam_P += local_displacement;
    camera->cam_COM = COM_new;
  }

  //---------------------------
}


}
