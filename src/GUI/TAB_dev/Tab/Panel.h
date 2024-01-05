#pragma once

#include <GUI/TAB_dev/Tab/Namespace.h>
#include <Utility/Specific/common.h>
#include <GUI/TAB_dev/Editor/Namespace.h>
#include <GUI/TAB_dev/Data/Namespace.h>
#include <GUI/TAB_dev/Tab/Namespace.h>

class GUI;

namespace gui::dev::tab{
class Command;
class Menu;
class Panel;


class Panel
{
public:
  //Constructor / Destructor
  Panel(GUI* gui);
  ~Panel();

public:
  //Main functions
  void create_panels();
  void draw_panels();

  //Subfunction
  void run_editors();

  bool show_database = true;
  
private:
  GUI* gui;
  gui::dev::tab::Menu* menu;
  gui::dev::editor::Command* command;
  gui::dev::data::Database* database;

  std::vector<gui::dev::editor::Editor*> vec_editor;
  int ID_editor = 0;
};

}
