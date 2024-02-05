#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::ope{class Node;}
namespace eng::ope{class Operation;}
namespace eng::ope{class Wheel;}
namespace eng::scene{class Scene;}
namespace eng::scene{class Database;}
namespace eng::cam{class Control;}
namespace eng::cam{class Manager;}
namespace utl::element{class Window;}


namespace eng::ope::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(eng::ope::Node* node_operation);
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
  eng::Node* node_engine;
  utl::element::Window* utl_window;
  eng::scene::Scene* sce_scene;
  eng::scene::Database* sce_database;
  eng::cam::Control* cam_control;
  eng::cam::Manager* cam_manager;
  eng::ope::Operation* ope_operation;
  eng::ope::Wheel* ope_wheel;
};

}
