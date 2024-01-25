#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/src/Namespace.h>
#include <GUI/Namespace.h>

namespace gui{class Node;}

namespace gui{
class Tab;


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
  gui::Tab* gui_tab;
};

}
