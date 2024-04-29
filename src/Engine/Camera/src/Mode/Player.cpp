#include "Player.h"

#include <Camera/Namespace.h>
#include <Vulkan/Namespace.h>


namespace cam::mode{

//Constructor / Destructor
Player::Player(cam::Node* node_camera){
  //---------------------------

  vk::Node* node_vulkan = node_camera->get_node_vulkan();

  this->vk_window = node_vulkan->get_vk_window();

  this->mouse_pose_old = vec2(0.0f);

  //---------------------------
}
Player::~Player(){}

//Camera movement
void Player::camera_forward(cam::Entity* camera, float speed){
  //---------------------------

  camera->cam_P += camera->cam_F * speed;

  //---------------------------
}
void Player::camera_backward(cam::Entity* camera, float speed){
  //---------------------------

  camera->cam_P -= camera->cam_F * speed;

  //---------------------------
}
void Player::camera_right(cam::Entity* camera, float speed){
  //---------------------------

  camera->cam_P += camera->cam_R * speed;

  //---------------------------
}
void Player::camera_left(cam::Entity* camera, float speed){
  //---------------------------

  camera->cam_P -= camera->cam_R * speed;

  //---------------------------
}
void Player::camera_up(cam::Entity* camera, float speed){
  //---------------------------

  camera->cam_P += camera->cam_U * speed;

  //---------------------------
}
void Player::camera_down(cam::Entity* camera, float speed){
  //---------------------------

  camera->cam_P -= camera->cam_U * speed;

  //---------------------------
}
void Player::camera_mouse(cam::Entity* camera){
  //---------------------------

  float& azimuth = camera->angle_azimuth;
  float& elevation = camera->angle_elevation;

  //Cursor movement
  vec2 mouse_pose = vk_window->get_mouse_pose();
  vec2 window_center = camera->panel_center;

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
void Player::camera_zoom(cam::Entity* camera, float speed){
  //---------------------------

  //Perspective zoom
  vec3 cam_forwardMove = camera->cam_F * speed * camera->velocity * vec3(0.1,0.1,0.1);
  camera->cam_P += cam_forwardMove;

  //---------------------------
}

//Camera matrix
mat4 Player::compute_camera_view(cam::Entity* camera){
  glm::mat4 cam_view = glm::mat4(1.0f);
  if(camera == nullptr) return cam_view;
  //---------------------------

  float azimuth = camera->angle_azimuth;
  float elevation = camera->angle_elevation;

  //Compute camera
  camera->cam_R = normalize(vec3(cos(azimuth - M_PI/2.0f), sin(azimuth - M_PI/2.0f), 0));
  camera->cam_F = vec3(cos(elevation) * cos(azimuth), cos(elevation) * sin(azimuth), sin(elevation));
  camera->cam_U = normalize(cross(camera->cam_R, camera->cam_F));
  vec3 cam_target = camera->cam_P + camera->cam_F;

  //Compute view matrix
  cam_view = lookAt(camera->cam_P, cam_target, camera->cam_U);

  camera->mat_view = cam_view;

  //---------------------------
  return cam_view;
}


}
