#pragma once

#include <Camera/src/Mode/Base.h>
#include <glm/glm.hpp>
#include <memory>

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
  void camera_forward(std::shared_ptr<cam::Entity> camera, float speed);
  void camera_backward(std::shared_ptr<cam::Entity> camera, float speed);
  void camera_right(std::shared_ptr<cam::Entity> camera, float speed);
  void camera_left(std::shared_ptr<cam::Entity> camera, float speed);
  void camera_up(std::shared_ptr<cam::Entity> camera, float speed);
  void camera_down(std::shared_ptr<cam::Entity> camera, float speed);
  void camera_mouse(std::shared_ptr<cam::Entity> camera);
  void camera_wheel(std::shared_ptr<cam::Entity> camera, float speed);
  void camera_zoom(std::shared_ptr<cam::Entity> camera, float speed);

  //Subfunction
  glm::mat4 compute_camera_view(std::shared_ptr<cam::Entity> camera);
  void rotate_by_angle(std::shared_ptr<cam::Entity> camera, glm::vec2 angle);
  void displace_camera_COM(std::shared_ptr<cam::Entity> camera, const glm::vec3& displacement);

private:
  vk::window::GLFW* vk_window;

  glm::vec3 origin;
};

}
