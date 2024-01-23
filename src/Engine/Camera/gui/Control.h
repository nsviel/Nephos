#pragma once


#include <Engine/Scene/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;


namespace gui::engine{

class Control
{
public:
  //Constructor / Destructor
  Control(Engine* engine);
  ~Control();

public:
  //Main function
  void run_control(ImVec2 center);

  //Keyboard
  void control_keyboard_camMove();

  //Mouse
  void control_mouse(ImVec2 center);
  void control_mouse_wheel();

private:
  Engine* engine;
  util::element::Window* utl_window;
  eng::scene::Scene* sce_scene;
  eng::scene::Database* sce_database;
  camera::src::Control* cam_control;
  camera::src::Manager* cam_manager;
  eng::ope::Operation* ope_operation;
};

}
