#pragma once

#include <TAB_dev/Tab_nsp.h>
#include <UTL_specific/common.h>

class GUI;

namespace gui::dev::panel{


class Command
{
public:
  //Constructor / Destructor
  Command(GUI* gui);
  ~Command();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunctions

private:
  GUI* gui;
  gui::dev::tab::Panel* gui_panel;
};

}
