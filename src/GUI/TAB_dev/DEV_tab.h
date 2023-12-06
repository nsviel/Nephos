#pragma once

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

  inline dev::Panel* get_panel(){return panel;}

private:
  GUI* gui;
  dev::Panel* panel;
  dev::DEV_command* dev_command;
  dev::Database* database;
  dev::Menu* menu;
};
