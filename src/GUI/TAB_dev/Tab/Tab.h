#pragma once

#include <GUI/TAB_dev/Tab/Namespace.h>
#include <UTL_specific/common.h>

class GUI;

namespace gui::dev::tab{
class Command;
class Menu;
class Panel;


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

  inline gui::dev::tab::Panel* get_panel(){return panel;}

private:
  GUI* gui;
  gui::dev::tab::Panel* panel;
  gui::dev::tab::Menu* menu;
  gui::dev::editor::Command* command;
  gui::dev::data::Database* database;
};

}
