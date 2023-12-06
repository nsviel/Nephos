#ifndef GUI_DEV_COMMAND_H
#define GUI_DEV_COMMAND_H

#include "../DEV_nsp.h"
#include <UTL_specific/common.h>

class GUI;
class DEV_panel;


class DEV_command
{
public:
  //Constructor / Destructor
  DEV_command(GUI* gui);
  ~DEV_command();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunctions

private:
  GUI* gui;
  DEV_panel* gui_dev_panel;
};

#endif
