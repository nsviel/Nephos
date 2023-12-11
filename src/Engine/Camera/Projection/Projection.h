#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>

class UTL_window;


namespace eng::camera::proj{

class Projection
{
public:
  Projection(UTL_window* utl_window);
  ~Projection();

public:
  mat4 compute_proj_perspective(eng::structure::Camera* camera);
  mat4 compute_proj_ortho(eng::structure::Camera* camera);

private:
  UTL_window* utl_window;
};

}
