#pragma once

#include <Engine/Camera/Namespace.h>
#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

namespace eng::camera::mode{


class Arcball : public eng::camera::mode::Base
{
public:
  Arcball(util::element::Window* utl_window);
  ~Arcball();

public:
  void camera_up(eng::data::Camera* camera, float speed);
  void camera_down(eng::data::Camera* camera, float speed);
  void camera_right(eng::data::Camera* camera, float speed);
  void camera_left(eng::data::Camera* camera, float speed);

  mat4 arcball_view_mat(eng::data::Camera* camera);
  void arcball_cam_mouse(eng::data::Camera* camera);
  vec2 arcball_mouse_angle();
  void rotate_by_angle(eng::data::Camera* camera, vec2 angle);

private:
};

}
