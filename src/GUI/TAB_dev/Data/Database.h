#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <Utility/Specific/common.h>

class GUI;

class UTL_database;


namespace gui::dev::data{

class Database : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Database(GUI* gui, bool* show_window, string name);
  ~Database();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void display_option();
  void combo_table();
  void display_table();

private:
  UTL_database* database;

  string path_db;
};

}
