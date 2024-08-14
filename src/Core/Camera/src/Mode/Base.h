#pragma once

#include <glm/glm.hpp>

namespace cam{class Entity;}


namespace cam::mode{

class Base
{
public:
  Base(){}
  ~Base(){}

public:
  //Camera movement
  virtual void camera_forward(cam::Entity* camera, float speed){}
  virtual void camera_backward(cam::Entity* camera, float speed){}
  virtual void camera_right(cam::Entity* camera, float speed){}
  virtual void camera_left(cam::Entity* camera, float speed){}
  virtual void camera_up(cam::Entity* camera, float speed){}
  virtual void camera_down(cam::Entity* camera, float speed){}
  virtual void camera_mouse(cam::Entity* camera){}
  virtual void camera_wheel(cam::Entity* camera, float speed){}
  virtual void camera_zoom(cam::Entity* camera, float speed){}

  //Camera matrix
  virtual glm::mat4 compute_camera_view(cam::Entity* camera){return glm::mat4(1);}
};

}
