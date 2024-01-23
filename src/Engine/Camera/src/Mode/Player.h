#pragma once

#include <Engine/Camera/Namespace.h>

#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace camera::src::mode{

class Player : public camera::src::mode::Base
{
public:
  Player(util::element::Window* utl_window);
  ~Player();

public:
  //Camera movement
  void camera_forward(utl::entity::Camera* camera, float speed);
  void camera_backward(utl::entity::Camera* camera, float speed);
  void camera_right(utl::entity::Camera* camera, float speed);
  void camera_left(utl::entity::Camera* camera, float speed);
  void camera_up(utl::entity::Camera* camera, float speed);
  void camera_down(utl::entity::Camera* camera, float speed);
  void camera_mouse(utl::entity::Camera* camera);
  void camera_zoom(utl::entity::Camera* camera, float speed);

  //Camera matrix
  mat4 compute_camera_view(utl::entity::Camera* camera);


private:
  vec2 mouse_pose_old;
};

}
