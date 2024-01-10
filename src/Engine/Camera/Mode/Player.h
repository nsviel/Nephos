#pragma once

#include <Engine/Camera/Namespace.h>
#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera::mode{

class Player : public eng::camera::mode::Base
{
public:
  Player(util::element::Window* utl_window);
  ~Player();

public:
  void camera_up(eng::data::Camera* camera, float speed);
  void camera_down(eng::data::Camera* camera, float speed);
  void camera_right(eng::data::Camera* camera, float speed);
  void camera_left(eng::data::Camera* camera, float speed);

  mat4 fp_view_mat(eng::data::Camera* camera);
  void fp_cam_mouse(eng::data::Camera* camera);

private:
  vec2 mouse_pose_old;
};

}
