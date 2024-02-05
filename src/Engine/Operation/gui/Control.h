#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::ope{class Operation;}
namespace utl::element{class Window;}
namespace eng::scene{class Scene;}
namespace eng::scene{class Database;}
namespace eng::cam{class Control;}
namespace eng::cam{class Manager;}

enum Wheel_mode{
  WHEEL_R_X = 0,
  WHEEL_R_Y = 1,
  WHEEL_R_Z = 2,
  WHEEL_CAM_Z = 3,
};


namespace eng::ope::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(eng::Node* engine);
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
  eng::Node* engine;
  utl::element::Window* utl_window;
  eng::scene::Scene* sce_scene;
  eng::scene::Database* sce_database;
  eng::cam::Control* cam_control;
  eng::cam::Manager* cam_manager;
  eng::ope::Operation* ope_operation;
};

}
