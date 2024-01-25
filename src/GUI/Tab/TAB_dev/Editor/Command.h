#pragma once

#include <GUI/Namespace.h>
#include <Utility/Specific/common.h>

namespace gui{class Node;}

namespace gui::dev::editor{


class Command
{
public:
  //Constructor / Destructor
  Command(gui::Node* gui);
  ~Command();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunctions

private:
  gui::Node* gui;
  //gui::dev::tab::Panel* gui_panel;
};

}
