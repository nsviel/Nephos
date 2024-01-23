#pragma once

#include <Engine/Data/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;


namespace ope::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(Engine* engine);
  ~Control();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard_oneAction();
  void control_keyboard_translation();

  //Mouse
  void control_mouse_wheel();

private:
  Engine* engine;
  util::element::Window* utl_window;
  eng::scene::Scene* sce_scene;
  eng::scene::Database* sce_database;
  camera::src::Control* cam_control;
  camera::src::Manager* cam_manager;
  ope::src::Operation* ope_operation;
};

}
