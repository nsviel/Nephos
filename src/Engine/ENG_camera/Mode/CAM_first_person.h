#ifndef CAM_FPS_H
#define CAM_FPS_H

#include "../struct_camera.h"
#include <ELE_specific/common.h>

class Window;


class CAM_first_person
{
public:
  CAM_first_person(Window* window);
  ~CAM_first_person();

public:
  mat4 fp_view_mat(Struct_camera* camera);
  void fp_cam_mouse(Struct_camera* camera);

private:
  Window* window;

  vec2 mouse_pose_old;
};

#endif
