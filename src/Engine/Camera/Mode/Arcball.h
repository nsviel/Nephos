#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera::mode{

class Arcball
{
public:
  Arcball(util::element::Window* utl_window);
  ~Arcball();

public:
  mat4 arcball_view_mat(eng::data::Camera* camera);
  void arcball_cam_mouse(eng::data::Camera* camera);
  vec2 arcball_mouse_angle();
  void rotate_by_angle(eng::data::Camera* camera, vec2 angle);

private:
  util::element::Window* utl_window;
};

}
