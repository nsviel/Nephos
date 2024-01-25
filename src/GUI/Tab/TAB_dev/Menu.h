#pragma once

#include <Utility/Specific/common.h>
#include <GUI/Namespace.h>

namespace gui::dev::tab{
class Panel;


class Menu
{
public:
  //Constructor / Destructor
  Menu(gui::dev::tab::Panel* panel);
  ~Menu();

public:
  //Main function
  void run_tab_menu();

  //Subfunctions
  void open_panels();

private:
  gui::dev::tab::Panel* panel;

};

}
