#pragma once

#include <TAB_dev/DEV_nsp.h>
#include <UTL_specific/common.h>


namespace dev{

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
  dev::Panel* panel;

};

}
