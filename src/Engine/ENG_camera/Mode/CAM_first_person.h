#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/UTL_specific/common.h>

class UTL_window;


class CAM_first_person
{
public:
  CAM_first_person(UTL_window* utl_window);
  ~CAM_first_person();

public:
  mat4 fp_view_mat(eng::structure::Camera* camera);
  void fp_cam_mouse(eng::structure::Camera* camera);

private:
  UTL_window* utl_window;

  vec2 mouse_pose_old;
};
