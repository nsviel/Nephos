#pragma once

#include <UTL_specific/common.h>

class GUI;
class Engine;
class UTL_window;
class ENG_camera;
class UTL_window;
class ENG_scene;
class Transformation;
class Struct_camera;


class RND_control
{
public:
  //Constructor / Destructor
  RND_control(GUI* gui);
  ~RND_control();

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
  ENG_camera* eng_camera;
  Transformation* transformManager;

  Struct_camera* camera;
};
