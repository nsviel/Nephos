#pragma once

#include <Utility/Specific/Common.h>

namespace cam{class Camera;}


namespace cam::mode{

class Base
{
public:
  Base(){}
  ~Base(){}

public:
  //Camera movement
  virtual void camera_forward(cam::Camera* camera, float speed){}
  virtual void camera_backward(cam::Camera* camera, float speed){}
  virtual void camera_right(cam::Camera* camera, float speed){}
  virtual void camera_left(cam::Camera* camera, float speed){}
  virtual void camera_up(cam::Camera* camera, float speed){}
  virtual void camera_down(cam::Camera* camera, float speed){}
  virtual void camera_mouse(cam::Camera* camera){}
  virtual void camera_wheel(cam::Camera* camera, float speed){}
  virtual void camera_zoom(cam::Camera* camera, float speed){}

  //Camera matrix
  virtual mat4 compute_camera_view(cam::Camera* camera){return mat4(1);}
};

}
