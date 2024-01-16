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
  virtual void camera_forward(eng::base::Camera* camera, float speed){}
  virtual void camera_backward(eng::base::Camera* camera, float speed){}
  virtual void camera_right(eng::base::Camera* camera, float speed){}
  virtual void camera_left(eng::base::Camera* camera, float speed){}
  virtual void camera_up(eng::base::Camera* camera, float speed){}
  virtual void camera_down(eng::base::Camera* camera, float speed){}
  virtual void camera_mouse(eng::base::Camera* camera){}
  virtual void camera_zoom(eng::base::Camera* camera, float speed){}

  //Camera matrix
  virtual mat4 compute_camera_view(eng::base::Camera* camera){return mat4(1);}

protected:
  util::element::Window* utl_window;
};

}
