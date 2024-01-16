#pragma once

#include <Engine/Camera/Namespace.h>
#include <Engine/Entity/Namespace.h>
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
  void camera_forward(eng::data::Camera* camera, float speed);
  void camera_backward(eng::data::Camera* camera, float speed);
  void camera_right(eng::data::Camera* camera, float speed);
  void camera_left(eng::data::Camera* camera, float speed);
  void camera_up(eng::data::Camera* camera, float speed);
  void camera_down(eng::data::Camera* camera, float speed);
  void camera_mouse(eng::data::Camera* camera);
  void camera_zoom(eng::data::Camera* camera, float speed);

  //Camera matrix
  mat4 compute_camera_view(eng::data::Camera* camera);


private:
  vec2 mouse_pose_old;
};

}
