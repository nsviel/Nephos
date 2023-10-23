#ifndef GUI_DEV_COMMAND_H
#define GUI_DEV_COMMAND_H

#include <Specific/common.h>

class GUI;


class GUI_dev_command
{
public:
  //Constructor / Destructor
  GUI_dev_command(GUI* gui);
  ~GUI_dev_command();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunctions

private:
  GUI* gui;
};

#endif
