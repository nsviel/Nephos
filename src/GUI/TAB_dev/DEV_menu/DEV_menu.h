#ifndef DEV_MENU_H
#define DEV_MENU_H

#include <UTL_specific/common.h>

class DEV_panel;


namespace dev{

class DEV_menu
{
public:
  //Constructor / Destructor
  DEV_menu(DEV_panel* panel);
  ~DEV_menu();

public:
  //Main function
  void run_tab_menu();

  //Subfunctions
  void open_panels();

private:
  DEV_panel* dev_panel;

};

}


#endif
