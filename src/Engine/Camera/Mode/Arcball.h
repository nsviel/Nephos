#pragma once

#include <Engine/Camera/Namespace.h>
#include <Utility/Base/Namespace.h>
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
  void camera_forward(eng::base::Camera* camera, float speed);
  void camera_backward(eng::base::Camera* camera, float speed);
  void camera_right(eng::base::Camera* camera, float speed);
  void camera_left(eng::base::Camera* camera, float speed);
  void camera_up(eng::base::Camera* camera, float speed);
  void camera_down(eng::base::Camera* camera, float speed);
  void camera_mouse(eng::base::Camera* camera);
  void camera_zoom(eng::base::Camera* camera, float speed);

  //Camera matrix
  mat4 compute_camera_view(eng::base::Camera* camera);

  //Subfunction
  void rotate_by_angle(eng::base::Camera* camera, vec2 angle);
  void displace_camera_COM(eng::base::Camera* camera, const vec3& displacement);

private:
  vec3 origin;
};

}
