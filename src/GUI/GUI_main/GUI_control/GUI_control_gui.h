#ifndef CONTROL_GUI_H
#define CONTROL_GUI_H

#include <ELE_specific/common.h>

class GUI;
class GUI_tab;
class ELE_window;


class GUI_control_gui
{
public:
  //Constructor / Destructor
  GUI_control_gui(GUI* gui);
  ~GUI_control_gui();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard_oneAction();

  //Mouse

private:
  ELE_window* ele_window;
  GUI_tab* gui_tab;
};

#endif
