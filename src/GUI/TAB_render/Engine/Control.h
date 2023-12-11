#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/UTL_specific/common.h>

class GUI;
class Engine;
class UTL_window;
class UTL_window;
class ENG_scene;
class Transformation;



namespace gui::engine{

class Control
{
public:
  //Constructor / Destructor
  Control(GUI* gui);
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
  UTL_window* utl_window;
  ENG_scene* eng_scene;
  eng::camera::Camera* eng_camera;
  Transformation* transformManager;

  eng::structure::Camera* camera;
};

}
