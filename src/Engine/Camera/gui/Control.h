#pragma once

#include <Utility/Specific/common.h>

namespace eng::cam{class Node;}
namespace eng::cam{class Control;}
namespace eng::cam{class Manager;}
namespace utl::element{class Window;}


namespace eng::cam::gui{

class Control
{
public:
  //Constructor / Destructor
  Control(eng::cam::Node* cam_node);
  ~Control();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard_camMove();

  //Mouse
  void control_mouse();
  void control_mouse_wheel();

private:
  utl::element::Window* utl_window;
  eng::cam::Control* cam_control;
  eng::cam::Manager* cam_manager;
};

}
