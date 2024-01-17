#pragma once

#include <Engine/Camera/Namespace.h>

#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera::mode{

class Player : public eng::camera::mode::Base
{
public:
  Player(util::element::Window* utl_window);
  ~Player();

public:
  //Camera movement
  void camera_forward(entity::Camera* camera, float speed);
  void camera_backward(entity::Camera* camera, float speed);
  void camera_right(entity::Camera* camera, float speed);
  void camera_left(entity::Camera* camera, float speed);
  void camera_up(entity::Camera* camera, float speed);
  void camera_down(entity::Camera* camera, float speed);
  void camera_mouse(entity::Camera* camera);
  void camera_zoom(entity::Camera* camera, float speed);

  //Camera matrix
  mat4 compute_camera_view(entity::Camera* camera);


private:
  vec2 mouse_pose_old;
};

}
