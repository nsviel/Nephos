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
  Control(Engine* engine, eng::data::Camera* camera);
  ~Control();

public:
  //Camera displacment
  void control_keyboard(string direction, bool fast);
  void control_mouse();

  //Camera mode
  void set_mode_projection(int value);
  void set_mode_view(int value);

private:
  eng::camera::mode::Arcball* mode_arcball;
  eng::camera::mode::Player* mode_player;

  eng::data::Camera* camera;
};

}
