#pragma once

#include <Engine/Camera/src/Mode/Base.h>
#include <Utility/Specific/Common.h>
#include <Utility/Element/Namespace.h>

namespace cam{class Node;}
namespace cam::mode{class Base;}
namespace vk::window{class GLFW;}
namespace utl::entity{class Camera;}


namespace cam::mode{

class Arcball : public cam::mode::Base
{
public:
  Arcball(cam::Node* node_camera);
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
  void camera_wheel(utl::entity::Camera* camera, float speed);
  void camera_zoom(utl::entity::Camera* camera, float speed);

  //Camera matrix
  mat4 compute_camera_view(utl::entity::Camera* camera);

  //Subfunction
  void rotate_by_angle(utl::entity::Camera* camera, vec2 angle);
  void displace_camera_COM(utl::entity::Camera* camera, const vec3& displacement);

private:
  vk::window::GLFW* vk_window;

  vec3 origin;
};

}
