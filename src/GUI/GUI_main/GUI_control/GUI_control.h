#ifndef CONTROL_GUI_H
#define CONTROL_GUI_H

#include <UTL_specific/common.h>

class GUI;
class GUI_tab;
class UTL_window;


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

#endif
