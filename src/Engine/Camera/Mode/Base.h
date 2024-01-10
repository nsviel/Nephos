#pragma once

#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>


namespace eng::camera::mode{

class Base
{
public:
  Base(util::element::Window* utl_window);
  ~Base();

public:
  virtual void camera_up(eng::data::Camera* camera, float speed){}
  virtual void camera_down(eng::data::Camera* camera, float speed){}
  virtual void camera_right(eng::data::Camera* camera, float speed){}
  virtual void camera_left(eng::data::Camera* camera, float speed){}

protected:
  util::element::Window* utl_window;
};

}
