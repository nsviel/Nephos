#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera::mode{

class First_person
{
public:
  First_person(util::element::Window* utl_window);
  ~First_person();

public:
  mat4 fp_view_mat(eng::structure::Camera* camera);
  void fp_cam_mouse(eng::structure::Camera* camera);

private:
  util::element::Window* utl_window;

  vec2 mouse_pose_old;
};

}
