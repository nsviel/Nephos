#pragma once

#include <GUI/Namespace.h>
#include <Utility/Specific/common.h>

class GUI;
namespace gui::dev::tab{class Command;}
namespace gui::dev::tab{class Menu;}
namespace gui::dev::tab{class Panel;}
namespace gui::dev::editor{class Command;}
namespace gui::dev::editor{class Editor;}
namespace gui::dev::data{class Database;}


namespace gui::dev::tab{

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
