#pragma once

#include <Utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera{

class Projection
{
public:
  Projection(util::element::Window* utl_window);
  ~Projection();

public:
  mat4 compute_proj_perspective(eng::base::Camera* camera);
  mat4 compute_proj_ortho(eng::base::Camera* camera);

private:
  util::element::Window* utl_window;
};

}
