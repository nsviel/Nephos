#pragma once

#include "../DEV_nsp.h"
#include <UTL_specific/common.h>

class GUI;
class DEV_panel;


namespace dev{

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

}
