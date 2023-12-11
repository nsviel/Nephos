#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>

class UTL_window;


namespace eng::camera::mode{

class Arcball
{
public:
  Arcball(UTL_window* utl_window);
  ~Arcball();

public:
  mat4 arcball_view_mat(eng::structure::Camera* camera);
  void arcball_cam_mouse(eng::structure::Camera* camera);
  vec2 arcball_mouse_angle();
  void arcball_viewport_angle(eng::structure::Camera* camera, vec2 angle);

private:
  UTL_window* utl_window;
};

}
