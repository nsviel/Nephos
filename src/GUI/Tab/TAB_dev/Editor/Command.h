#pragma once

#include <GUI/Namespace.h>
#include <Utility/Specific/common.h>

class GUI;

namespace gui::dev::editor{


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
  //gui::dev::tab::Panel* gui_panel;
};

}
