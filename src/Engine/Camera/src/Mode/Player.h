#pragma once

#include <Engine/Camera/src/Mode/Base.h>
#include <glm/glm.hpp>

namespace cam{class Node;}
namespace cam{class Entity;}
namespace vk::window{class GLFW;}


namespace cam::mode{

class Player : public cam::mode::Base
{
public:
  Player(cam::Node* node_camera);
  ~Player();

public:
  //Camera movement
  void camera_forward(cam::Entity* camera, float speed);
  void camera_backward(cam::Entity* camera, float speed);
  void camera_right(cam::Entity* camera, float speed);
  void camera_left(cam::Entity* camera, float speed);
  void camera_up(cam::Entity* camera, float speed);
  void camera_down(cam::Entity* camera, float speed);
  void camera_mouse(cam::Entity* camera);
  void camera_zoom(cam::Entity* camera, float speed);

  //Camera matrix
  glm::mat4 compute_camera_view(cam::Entity* camera);

private:
  vk::window::GLFW* vk_window;

  vec2 mouse_pose_old;
};

}
