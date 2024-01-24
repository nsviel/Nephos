#pragma once

#include <Engine/Camera/src/Mode/Base.h>
#include <Utility/Specific/common.h>

namespace utl::element{class Window;}


namespace eng::cam::mode{

class Base
{
public:
  Base(utl::element::Window* utl_window);
  ~Base();

public:
  //Camera movement
  virtual void camera_forward(utl::entity::Camera* camera, float speed){}
  virtual void camera_backward(utl::entity::Camera* camera, float speed){}
  virtual void camera_right(utl::entity::Camera* camera, float speed){}
  virtual void camera_left(utl::entity::Camera* camera, float speed){}
  virtual void camera_up(utl::entity::Camera* camera, float speed){}
  virtual void camera_down(utl::entity::Camera* camera, float speed){}
  virtual void camera_mouse(utl::entity::Camera* camera){}
  virtual void camera_zoom(utl::entity::Camera* camera, float speed){}

  //Camera matrix
  virtual mat4 compute_camera_view(utl::entity::Camera* camera){return mat4(1);}

protected:
  utl::element::Window* utl_window;
};

}
