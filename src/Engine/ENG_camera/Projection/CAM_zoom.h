#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/UTL_specific/common.h>

class UTL_window;


class CAM_zoom
{
public:
  CAM_zoom(UTL_window* utl_window);
  ~CAM_zoom();

public:
  void compute_zoom_optic(eng::structure::Struct_camera* camera, float value);
  void compute_zoom_position(eng::structure::Struct_camera* camera, float value);

private:
};
