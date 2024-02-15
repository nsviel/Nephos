#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

namespace eng::cam{class Node;}


namespace eng::cam{

class Projection
{
public:
  Projection(eng::cam::Node* node_camera);
  ~Projection();

public:
  //Main function
  mat4 compute_proj_perspective(utl::entity::Camera* camera);
  mat4 compute_proj_ortho(utl::entity::Camera* camera);

  //Subfunction
  void ortho_zoom(utl::entity::Camera* camera, float value);

private:
  utl::element::Window* utl_window;
};

}
