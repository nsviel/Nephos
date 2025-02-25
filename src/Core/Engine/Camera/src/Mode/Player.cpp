#include "Player.h"

#include <Engine/Camera/Namespace.h>
#include <Vulkan/Namespace.h>
#include <glm/gtc/matrix_transform.hpp>


namespace cam::mode{

//Constructor / Destructor
Player::Player(cam::Node* node_camera){
  //---------------------------

  vk::Node* node_vulkan = node_camera->get_node_vulkan();

  this->vk_window = node_vulkan->get_vk_window();

  this->mouse_pose_old = glm::vec2(0.0f);

  //---------------------------
}
Player::~Player(){}

//Camera movement
void Player::camera_forward(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  camera->cam_pose += camera->cam_forward * speed;

  //---------------------------
}
void Player::camera_backward(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  camera->cam_pose -= camera->cam_forward * speed;

  //---------------------------
}
void Player::camera_right(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  camera->cam_pose += camera->cam_right * speed;

  //---------------------------
}
void Player::camera_left(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  camera->cam_pose -= camera->cam_right * speed;

  //---------------------------
}
void Player::camera_up(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  camera->cam_pose += camera->cam_up * speed;

  //---------------------------
}
void Player::camera_down(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  camera->cam_pose -= camera->cam_up * speed;

  //---------------------------
}
void Player::camera_mouse(std::shared_ptr<cam::Entity> camera){
  //---------------------------

  float& azimuth = camera->angle_azimuth;
  float& elevation = camera->angle_elevation;

  //Cursor movement
  glm::vec2 mouse_pose = vk_window->get_mouse_pose();
  glm::vec2 window_center = camera->panel_center;

  if(mouse_pose != mouse_pose_old){
    vk_window->set_mouse_pose(window_center);

    // Compute new orientation
    azimuth += camera->player_mouse_sensibility.x * float(window_center.x - mouse_pose.x);
    elevation += camera->player_mouse_sensibility.y * float(window_center.y - mouse_pose.y);

    //Limites of camera rotation
    if(elevation > M_PI/2) elevation = M_PI/2;
    if(elevation < -M_PI/2) elevation = -M_PI/2;
    if(azimuth > M_PI*2) azimuth = 0;
    if(azimuth < -M_PI*2) azimuth = 0;

    //Setup mouse
    mouse_pose_old = mouse_pose;
  }

  //---------------------------
}
void Player::camera_zoom(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  //Perspective zoom
  camera->cam_pose += camera->cam_forward * speed * camera->velocity * glm::vec3(0.1, 0.1, 0.1);

  //---------------------------
}
void Player::camera_wheel(std::shared_ptr<cam::Entity> camera, float speed){
  //---------------------------

  this->camera_zoom(camera, speed);

  //---------------------------
}

//Camera matrix
glm::mat4 Player::compute_camera_view(std::shared_ptr<cam::Entity> camera){
  glm::mat4 cam_view = glm::mat4(1.0f);
  if(camera == nullptr) return cam_view;
  //---------------------------

  float azimuth = camera->angle_azimuth;
  float elevation = camera->angle_elevation;

  //Compute camera
  camera->cam_right = normalize(glm::vec3(cos(azimuth - M_PI/2.0f), sin(azimuth - M_PI/2.0f), 0));
  camera->cam_forward = glm::vec3(cos(elevation) * cos(azimuth), cos(elevation) * sin(azimuth), sin(elevation));
  camera->cam_up = normalize(cross(camera->cam_right, camera->cam_forward));
  glm::vec3 cam_target = camera->cam_pose + camera->cam_forward;

  //Compute view matrix
  cam_view = glm::lookAt(camera->cam_pose, cam_target, camera->cam_up);
  camera->mat_view = cam_view;

  //---------------------------
  return cam_view;
}


}
