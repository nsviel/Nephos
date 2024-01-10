#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Engine/Camera/Mode/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

class Engine;


namespace eng::camera{

class Control
{
public:
  Control(Engine* engine);
  ~Control();

public:
  //Main function
  void control(string what, bool fast);

private:
  eng::camera::mode::Arcball* cam_arcball;

  eng::data::Camera* camera;
};

}
