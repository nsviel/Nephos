#pragma once

#include <UTL_specific/common.h>
#include <GUI/TAB_dev/Tab/Namespace.h>


namespace gui::dev::tab{

class Menu
{
public:
  //Constructor / Destructor
  Menu(Panel* panel);
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
