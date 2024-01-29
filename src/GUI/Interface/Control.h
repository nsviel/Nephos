#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}
namespace gui::interface{class Tab;}
namespace utl::element{class Window;}


namespace gui::interface{

class Control
{
public:
  //Constructor / Destructor
  Control(gui::Node* gui);
  ~Control();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard_oneAction();

  //Mouse

private:
  utl::element::Window* utl_window;
  gui::interface::Tab* gui_tab;
};

}
