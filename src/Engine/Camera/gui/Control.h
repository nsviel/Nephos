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
  void control_keyboard_oneAction();
  void control_keyboard_camMove();
  void control_keyboard_translation();

  //Mouse
  void control_mouse(ImVec2 center);
  void control_mouse_wheel();

private:
  Engine* engine;
  util::element::Window* utl_window;
  eng::scene::Scene* sce_scene;
  eng::scene::Database* sce_database;
  eng::camera::Control* cam_control;
  eng::camera::Manager* cam_manager;
  eng::ope::Operation* ope_operation;
};

}
