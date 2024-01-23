#pragma once


#include <Engine/Data/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;


namespace eng::cam::gui{

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
  utl::element::Window* utl_window;
  eng::scene::Scene* sce_scene;
  eng::scene::Database* sce_database;
  eng::cam::Control* cam_control;
  eng::cam::Manager* cam_manager;
  eng::ope::Operation* ope_operation;
};

}
