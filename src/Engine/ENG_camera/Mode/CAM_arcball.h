#ifndef CAM_ARCBALL_H
#define CAM_ARCBALL_H

#include "../Struct_camera.h"
#include <ELE_specific/common.h>

class ELE_window;


class CAM_arcball
{
public:
  CAM_arcball(ELE_window* ele_window);
  ~CAM_arcball();

public:
  mat4 arcball_view_mat(Struct_camera* camera);
  void arcball_cam_mouse(Struct_camera* camera);
  vec2 arcball_mouse_angle();
  void arcball_viewport_angle(Struct_camera* camera, vec2 angle);

private:
  ELE_window* ele_window;
};

#endif
