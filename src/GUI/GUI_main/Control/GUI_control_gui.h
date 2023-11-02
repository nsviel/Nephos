#ifndef CONTROL_GUI_H
#define CONTROL_GUI_H

#include <Specific/common.h>

class GUI;
class GUI_tab;
class Window;


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
  Window* window;
  GUI_tab* gui_tab;
};

#endif
