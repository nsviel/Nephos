#pragma once

#include <Engine/Entity/Namespace.h>
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
  virtual void camera_forward(eng::data::Camera* camera, float speed){}
  virtual void camera_backward(eng::data::Camera* camera, float speed){}
  virtual void camera_right(eng::data::Camera* camera, float speed){}
  virtual void camera_left(eng::data::Camera* camera, float speed){}
  virtual void camera_up(eng::data::Camera* camera, float speed){}
  virtual void camera_down(eng::data::Camera* camera, float speed){}
  virtual void camera_mouse(eng::data::Camera* camera){}
  virtual void camera_zoom(eng::data::Camera* camera, float speed){}

  //Camera matrix
  virtual mat4 compute_camera_view(eng::data::Camera* camera){return mat4(1);}

protected:
  util::element::Window* utl_window;
};

}
