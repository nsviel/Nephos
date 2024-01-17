#pragma once


#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera{

class Projection
{
public:
  Projection(util::element::Window* utl_window);
  ~Projection();

public:
  mat4 compute_proj_perspective(entity::Camera* camera);
  mat4 compute_proj_ortho(entity::Camera* camera);

private:
  util::element::Window* utl_window;
};

}
