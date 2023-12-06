#ifndef DEV_TAB_H
#define DEV_TAB_H

#include "DEV_nsp.h"
#include <UTL_specific/common.h>

class GUI;


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

  inline dev::DEV_panel* get_dev_panel(){return dev_panel;}

private:
  GUI* gui;
  dev::DEV_panel* dev_panel;
  dev::DEV_command* dev_command;
  dev::DEV_database* dev_database;
  dev::DEV_menu* dev_menu;
};

#endif
