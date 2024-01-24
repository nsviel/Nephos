#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/src/Namespace.h>


namespace eng::cam{

class Projection
{
public:
  Projection(utl::element::Window* utl_window);
  ~Projection();

public:
  mat4 compute_proj_perspective(utl::entity::Camera* camera);
  mat4 compute_proj_ortho(utl::entity::Camera* camera);

private:
  utl::element::Window* utl_window;
};

}
