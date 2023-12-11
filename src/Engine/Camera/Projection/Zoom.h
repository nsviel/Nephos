#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/UTL_specific/common.h>

class UTL_window;


namespace eng::camera::proj{

class Zoom
{
public:
  Zoom(UTL_window* utl_window);
  ~Zoom();

public:
  void compute_zoom_optic(eng::structure::Camera* camera, float value);
  void compute_zoom_position(eng::structure::Camera* camera, float value);

private:
};

}
