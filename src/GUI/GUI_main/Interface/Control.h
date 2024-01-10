#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>
#include <GUI/GUI_main/Namespace.h>

class GUI;

namespace gui{
class Tab;


class Control
{
public:
  //Constructor / Destructor
  Control(GUI* gui);
  ~Control();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard_oneAction();

  //Mouse

private:
  util::element::Window* utl_window;
  gui::Tab* gui_tab;
};

}
