#pragma once

#include <UTL_specific/common.h>

class GUI;
class GUI_tab;
class UTL_window;


namespace gui{

class GUI_control
{
public:
  //Constructor / Destructor
  GUI_control(GUI* gui);
  ~GUI_control();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard_oneAction();

  //Mouse

private:
  UTL_window* utl_window;
  GUI_tab* gui_tab;
};

}
