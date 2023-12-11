#pragma once

#include <Utility/Specific/common.h>
#include <GUI/GUI_main/Node/Namespace.h>

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
