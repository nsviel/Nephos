#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera::proj{

class Zoom
{
public:
  Zoom(util::element::UTL_window* utl_window);
  ~Zoom();

public:
  void compute_zoom_optic(eng::structure::Camera* camera, float value);
  void compute_zoom_position(eng::structure::Camera* camera, float value);

private:
};

}
