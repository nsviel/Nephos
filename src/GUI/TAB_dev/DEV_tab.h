#ifndef DEV_TAB_H
#define DEV_TAB_H

#include "DEV_nsp.h"
#include <UTL_specific/common.h>

class GUI;
class DEV_code_editor;
class DEV_panel;
class DEV_command;
class DEV_database;


class DEV_tab
{
public:
  //Constructor / Destructor
  DEV_tab(GUI* gui);
  ~DEV_tab();

public:
  //Main functions
  void create_panels();
  void draw_panels();

  inline DEV_panel* get_dev_panel(){return dev_panel;}

private:
  GUI* gui;
  DEV_panel* dev_panel;
  DEV_command* dev_command;
  DEV_database* dev_database;
  dev::DEV_menu* dev_menu;
};

#endif
