#pragma once

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class GUI;
class Struct_vulkan;
class UTL_database;


namespace dev{

class Database : public BASE_panel
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
  void display_data();

private:
  UTL_database* database;

  string path_database;
};

}
