#pragma once

#include "../Struct_camera.h"
#include <Utility/UTL_specific/common.h>

class UTL_window;


class CAM_arcball
{
public:
  CAM_arcball(UTL_window* utl_window);
  ~CAM_arcball();

public:
  mat4 arcball_view_mat(Struct_camera* camera);
  void arcball_cam_mouse(Struct_camera* camera);
  vec2 arcball_mouse_angle();
  void arcball_viewport_angle(Struct_camera* camera, vec2 angle);

private:
  UTL_window* utl_window;
};
