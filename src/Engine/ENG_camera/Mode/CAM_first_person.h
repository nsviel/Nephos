#ifndef CAM_FPS_H
#define CAM_FPS_H

#include "../Struct_camera.h"
#include <ELE_specific/common.h>

class UTL_window;


class CAM_first_person
{
public:
  CAM_first_person(UTL_window* utl_window);
  ~CAM_first_person();

public:
  mat4 fp_view_mat(Struct_camera* camera);
  void fp_cam_mouse(Struct_camera* camera);

private:
  UTL_window* utl_window;

  vec2 mouse_pose_old;
};

#endif
