#pragma once

#include <Utility/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera::mode{

class Base
{
public:
  Base(util::element::Window* utl_window);
  ~Base();

public:
  //Camera movement
  virtual void camera_forward(entity::Camera* camera, float speed){}
  virtual void camera_backward(entity::Camera* camera, float speed){}
  virtual void camera_right(entity::Camera* camera, float speed){}
  virtual void camera_left(entity::Camera* camera, float speed){}
  virtual void camera_up(entity::Camera* camera, float speed){}
  virtual void camera_down(entity::Camera* camera, float speed){}
  virtual void camera_mouse(entity::Camera* camera){}
  virtual void camera_zoom(entity::Camera* camera, float speed){}

  //Camera matrix
  virtual mat4 compute_camera_view(entity::Camera* camera){return mat4(1);}

protected:
  util::element::Window* utl_window;
};

}
