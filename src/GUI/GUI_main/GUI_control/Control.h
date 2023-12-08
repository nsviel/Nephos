#pragma once

#include <UTL_specific/common.h>
#include <GUI_main/GUI_nsp.h>

class GUI;
class UTL_window;

namespace gui{
class GUI_tab;


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
  gui::GUI_tab* gui_tab;
};

}
