#pragma once

#include <Camera/src/Mode/Base.h>
#include <glm/glm.hpp>
#include <memory>

namespace cam{class Node;}
namespace cam{class Entity;}
namespace vk::interface{class Window;}


namespace cam::mode{

class Player : public cam::mode::Base
{
public:
  Player(cam::Node* node_camera);
  ~Player();

public:
  //Camera movement
  void camera_forward(std::shared_ptr<cam::Entity> camera, float speed);
  void camera_backward(std::shared_ptr<cam::Entity> camera, float speed);
  void camera_right(std::shared_ptr<cam::Entity> camera, float speed);
  void camera_left(std::shared_ptr<cam::Entity> camera, float speed);
  void camera_up(std::shared_ptr<cam::Entity> camera, float speed);
  void camera_down(std::shared_ptr<cam::Entity> camera, float speed);
  void camera_mouse(std::shared_ptr<cam::Entity> camera);
  void camera_zoom(std::shared_ptr<cam::Entity> camera, float speed);
  void camera_wheel(std::shared_ptr<cam::Entity> camera, float speed);

  //Camera matrix
  glm::mat4 compute_camera_view(std::shared_ptr<cam::Entity> camera);

private:
  vk::interface::Window* vk_window;

  glm::vec2 mouse_pose_old;
};

}
