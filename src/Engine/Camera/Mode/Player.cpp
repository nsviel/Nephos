#include "Player.h"


namespace eng::camera::mode{

//Constructor / Destructor
Player::Player(util::element::Window* utl_window) : Base(utl_window){
  //---------------------------

  this->mouse_pose_old = vec2(0.0f);

  //---------------------------
}
Player::~Player(){}

mat4 Player::fp_view_mat(eng::data::Camera* camera){
  //---------------------------

  float azimuth = camera->angle_azimuth;
  float elevation = camera->angle_elevation;

  //Compute camera
  camera->cam_R = normalize(vec3(cos(azimuth - M_PI/2.0f), sin(azimuth - M_PI/2.0f), 0));
  camera->cam_F = vec3(cos(elevation) * cos(azimuth), cos(elevation) * sin(azimuth), sin(elevation));
  camera->cam_U = normalize(cross(camera->cam_R, camera->cam_F));
  vec3 cam_target = camera->cam_P + camera->cam_F;

  //Compute view matrix
  mat4 cam_view = lookAt(camera->cam_P, cam_target, camera->cam_U);

  camera->mat_view = cam_view;

  //---------------------------
  return cam_view;
}
void Player::fp_cam_mouse(eng::data::Camera* camera){
  //---------------------------

  float& azimuth = camera->angle_azimuth;
  float& elevation = camera->angle_elevation;

  //Cursor movement
  vec2 mouse_pose = utl_window->get_mouse_pose();
  vec2 window_center = utl_window->get_window_center();

  if(mouse_pose != mouse_pose_old){
    utl_window->set_mouse_pose(window_center);

    // Compute new orientation
    azimuth += camera->speed_mouse * float(window_center.x - mouse_pose.x);
    elevation += camera->speed_mouse * float(window_center.y - mouse_pose.y);

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

}
