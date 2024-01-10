#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera{

class Zoom
{
public:
  Zoom(util::element::Window* utl_window);
  ~Zoom();

public:
  void compute_zoom_optic(eng::data::Camera* camera, float value);
  void compute_zoom_position(eng::data::Camera* camera, float value);

private:
};

}
