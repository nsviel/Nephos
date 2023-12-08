#pragma once

#include <TAB_dev/Dev_nsp.h>
#include <UTL_specific/common.h>

class GUI;
class Panel;


namespace dev{

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
  Panel* gui_panel;
};

}
