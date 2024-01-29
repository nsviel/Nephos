#pragma once

#include <GUI/Namespace.h>
#include <Utility/Specific/common.h>

namespace gui{class Node;}
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
  Panel(gui::Node* gui);
  ~Panel();

public:
  //Main functions
  void init_tab();
  void draw_tab();

  //Subfunction
  void run_editors();

  bool show_database = true;

private:
  gui::Node* gui;
  gui::dev::tab::Menu* menu;
  gui::dev::editor::Command* command;
  gui::dev::data::Database* database;

  std::vector<gui::dev::editor::Editor*> vec_editor;
  int ID_editor = 0;
};

}
