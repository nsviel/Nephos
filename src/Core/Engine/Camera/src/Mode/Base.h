#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace cam{class Entity;}


namespace cam::mode{

class Base
{
public:
  Base(){}
  ~Base(){}

public:
  //Camera movement
  virtual void camera_forward(std::shared_ptr<cam::Entity> camera, float speed){}
  virtual void camera_backward(std::shared_ptr<cam::Entity> camera, float speed){}
  virtual void camera_right(std::shared_ptr<cam::Entity> camera, float speed){}
  virtual void camera_left(std::shared_ptr<cam::Entity> camera, float speed){}
  virtual void camera_up(std::shared_ptr<cam::Entity> camera, float speed){}
  virtual void camera_down(std::shared_ptr<cam::Entity> camera, float speed){}
  virtual void camera_mouse(std::shared_ptr<cam::Entity> camera){}
  virtual void camera_wheel(std::shared_ptr<cam::Entity> camera, float speed){}
  virtual void camera_zoom(std::shared_ptr<cam::Entity> camera, float speed){}

  //Camera matrix
  virtual glm::mat4 compute_camera_view(std::shared_ptr<cam::Entity> camera){return glm::mat4(1);}
};

}
