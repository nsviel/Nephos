#pragma once

#include <UTL_specific/common.h>
#include <GUI_main/Node/Namespace.h>

class GUI;
class UTL_window;

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
  UTL_window* utl_window;
  gui::Tab* gui_tab;
};

}
