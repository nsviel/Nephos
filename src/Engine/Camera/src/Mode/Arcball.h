#pragma once

#include <Camera/src/Mode/Base.h>
#include <glm/glm.hpp>

namespace cam{class Node;}
namespace cam{class Entity;}
namespace vk::window{class GLFW;}


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

  //Subfunction
  mat4 compute_camera_view(cam::Entity* camera);
  void rotate_by_angle(cam::Entity* camera, vec2 angle);
  void displace_camera_COM(cam::Entity* camera, const glm::vec3& displacement);

private:
  vk::window::GLFW* vk_window;

  glm::vec3 origin;
};

}
