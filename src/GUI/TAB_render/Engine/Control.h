#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/Data/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>

class GUI;
class Engine;


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
  util::element::Window* utl_window;
  eng::scene::Operation* sce_operation;
  eng::scene::Scene* sce_scene;
  eng::scene::Database* sce_database;
  eng::camera::Node* node_camera;
  eng::camera::Control* cam_control;

  eng::data::Camera* camera;
};

}
