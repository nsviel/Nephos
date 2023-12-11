#pragma once

#include "../Struct_camera.h"
#include <Utility/UTL_specific/common.h>

class UTL_window;


class CAM_zoom
{
public:
  CAM_zoom(UTL_window* utl_window);
  ~CAM_zoom();

public:
  void compute_zoom_optic(Struct_camera* camera, float value);
  void compute_zoom_position(Struct_camera* camera, float value);

private:
};
