#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>

class UTL_window;


namespace eng::camera::mode{

class First_person
{
public:
  First_person(UTL_window* utl_window);
  ~First_person();

public:
  mat4 fp_view_mat(eng::structure::Camera* camera);
  void fp_cam_mouse(eng::structure::Camera* camera);

private:
  UTL_window* utl_window;

  vec2 mouse_pose_old;
};

}
