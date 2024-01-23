#pragma once

#include <Engine/Camera/Namespace.h>

#include <Utility/Specific/common.h>
#include <Utility/Element/src/Namespace.h>

namespace camera::src::mode{


class Arcball : public camera::src::mode::Base
{
public:
  Arcball(utl::element::Window* utl_window);
  ~Arcball();

public:
  //Camera movement
  void camera_forward(utl::entity::Camera* camera, float speed);
  void camera_backward(utl::entity::Camera* camera, float speed);
  void camera_right(utl::entity::Camera* camera, float speed);
  void camera_left(utl::entity::Camera* camera, float speed);
  void camera_up(utl::entity::Camera* camera, float speed);
  void camera_down(utl::entity::Camera* camera, float speed);
  void camera_mouse(utl::entity::Camera* camera);
  void camera_zoom(utl::entity::Camera* camera, float speed);

  //Camera matrix
  mat4 compute_camera_view(utl::entity::Camera* camera);

  //Subfunction
  void rotate_by_angle(utl::entity::Camera* camera, vec2 angle);
  void displace_camera_COM(utl::entity::Camera* camera, const vec3& displacement);

private:
  vec3 origin;
};

}
