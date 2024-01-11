#pragma once

#include <Engine/Camera/Namespace.h>
#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

namespace eng::camera::mode{


class Arcball : public eng::camera::mode::Base
{
public:
  Arcball(util::element::Window* utl_window);
  ~Arcball();

public:
  //Camera movement
  void camera_forward(eng::data::Camera* camera, float speed);
  void camera_backward(eng::data::Camera* camera, float speed);
  void camera_right(eng::data::Camera* camera, float speed);
  void camera_left(eng::data::Camera* camera, float speed);
  void camera_up(eng::data::Camera* camera, float speed);
  void camera_down(eng::data::Camera* camera, float speed);
  void camera_mouse(eng::data::Camera* camera);
  void camera_zoom(eng::data::Camera* camera, float speed);

  //Camera matrix
  mat4 compute_camera_view(eng::data::Camera* camera);

  //Subfunction
  void rotate_by_angle(eng::data::Camera* camera, vec2 angle);
  void displace_camera_COM(eng::data::Camera* camera, const vec3& displacement);

private:
  vec3 origin;
};

}
