#pragma once

#include <TAB_dev/DEV_nsp.h>
#include <UTL_specific/common.h>

class GUI;

namespace dev{
class Command;
class Menu;


class Tab
{
public:
  //Constructor / Destructor
  Tab(GUI* gui);
  ~Tab();

public:
  //Main functions
  void create_panels();
  void draw_panels();

  inline dev::Panel* get_panel(){return panel;}

private:
  GUI* gui;
  dev::Panel* panel;
  dev::Command* command;
  dev::Database* database;
  dev::Menu* menu;
};

}
