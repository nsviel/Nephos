#pragma once

#include <Engine/Data/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;
namespace eng::ope{class Operation;}


namespace eng::ope::gui{

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
  utl::element::Window* utl_window;
  eng::scene::Scene* sce_scene;
  eng::scene::Database* sce_database;
  eng::cam::Control* cam_control;
  eng::cam::Manager* cam_manager;
  eng::ope::Operation* ope_operation;
};

}
