#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace ope{class Node;}
namespace ope{class Operation;}
namespace ope{class Wheel;}
namespace eng::scene{class Database;}
namespace eng::scene{class Set;}
namespace eng::cam{class Control;}
namespace eng::cam{class Manager;}
namespace utl::element{class Window;}


namespace ope::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(ope::Node* node_operation);
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
  eng::scene::Database* sce_database;
  eng::scene::Set* sce_set;
  eng::cam::Control* cam_control;
  eng::cam::Manager* cam_manager;
  ope::Operation* ope_operation;
  ope::Wheel* ope_wheel;
};

}
