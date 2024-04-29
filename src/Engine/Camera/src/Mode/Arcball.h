#pragma once

#include <Engine/Camera/src/Mode/Base.h>
#include <Utility/Specific/Common.h>
#include <Utility/Element/Namespace.h>

namespace cam{class Node;}
namespace cam::mode{class Base;}
namespace vk::window{class GLFW;}
namespace cam{class Entity;}


namespace cam::mode{

class Arcball : public cam::mode::Base
{
public:
  Arcball(cam::Node* node_camera);
  ~Arcball();

public:
  //Camera movement
  void camera_forward(cam::Entity* camera, float speed);
  void camera_backward(cam::Entity* camera, float speed);
  void camera_right(cam::Entity* camera, float speed);
  void camera_left(cam::Entity* camera, float speed);
  void camera_up(cam::Entity* camera, float speed);
  void camera_down(cam::Entity* camera, float speed);
  void camera_mouse(cam::Entity* camera);
  void camera_wheel(cam::Entity* camera, float speed);
  void camera_zoom(cam::Entity* camera, float speed);

  //Camera matrix
  mat4 compute_camera_view(cam::Entity* camera);

  //Subfunction
  void rotate_by_angle(cam::Entity* camera, vec2 angle);
  void displace_camera_COM(cam::Entity* camera, const vec3& displacement);

private:
  vk::window::GLFW* vk_window;

  vec3 origin;
};

}
