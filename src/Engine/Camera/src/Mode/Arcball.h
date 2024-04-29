#pragma once

#include <Engine/Camera/src/Mode/Base.h>
#include <Utility/Specific/Common.h>
#include <Utility/Element/Namespace.h>

namespace cam{class Node;}
namespace cam::mode{class Base;}
namespace vk::window{class GLFW;}
namespace cam{class Camera;}


namespace cam::mode{

class Arcball : public cam::mode::Base
{
public:
  Arcball(cam::Node* node_camera);
  ~Arcball();

public:
  //Camera movement
  void camera_forward(cam::Camera* camera, float speed);
  void camera_backward(cam::Camera* camera, float speed);
  void camera_right(cam::Camera* camera, float speed);
  void camera_left(cam::Camera* camera, float speed);
  void camera_up(cam::Camera* camera, float speed);
  void camera_down(cam::Camera* camera, float speed);
  void camera_mouse(cam::Camera* camera);
  void camera_wheel(cam::Camera* camera, float speed);
  void camera_zoom(cam::Camera* camera, float speed);

  //Camera matrix
  mat4 compute_camera_view(cam::Camera* camera);

  //Subfunction
  void rotate_by_angle(cam::Camera* camera, vec2 angle);
  void displace_camera_COM(cam::Camera* camera, const vec3& displacement);

private:
  vk::window::GLFW* vk_window;

  vec3 origin;
};

}
