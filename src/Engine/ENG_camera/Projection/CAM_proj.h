#pragma once

#include <Engine/Base/Struct_camera.h>
#include <Utility/UTL_specific/common.h>

class UTL_window;


class CAM_proj
{
public:
  CAM_proj(UTL_window* utl_window);
  ~CAM_proj();

public:
  mat4 compute_proj_perspective(Struct_camera* camera);
  mat4 compute_proj_ortho(Struct_camera* camera);

private:
  UTL_window* utl_window;
};
