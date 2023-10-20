#ifndef CONTROL_EDITOR_H
#define CONTROL_EDITOR_H

#include <Specific/common.h>

class GUI_editor_text;


class GUI_control_editor
{
public:
  //Constructor / Destructor
  GUI_control_editor(GUI_editor_text* editor);
  ~GUI_control_editor();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard_oneAction();

  //Mouse

private:
  GUI_editor_text* editor;
};

#endif
