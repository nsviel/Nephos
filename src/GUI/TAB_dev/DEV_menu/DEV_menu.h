#ifndef GUI_DEV_MENU_H
#define GUI_DEV_MENU_H

#include <UTL_specific/common.h>

class GUI;
class DEV_tab;


class DEV_menu
{
public:
  //Constructor / Destructor
  DEV_menu(GUI* gui);
  ~DEV_menu();

public:
  //Main function
  void run_tab_menu();

  //Subfunctions

private:
  DEV_tab* dev_tab;

};


#endif
