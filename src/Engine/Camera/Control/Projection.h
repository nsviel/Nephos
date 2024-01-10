#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera{

class Projection
{
public:
  Projection(util::element::Window* utl_window);
  ~Projection();

public:
  mat4 compute_proj_perspective(eng::data::Camera* camera);
  mat4 compute_proj_ortho(eng::data::Camera* camera);

private:
  util::element::Window* utl_window;
};

}
