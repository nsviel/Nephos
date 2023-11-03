#ifndef GUI_DATABASE_H
#define GUI_DATABASE_H

#include <RES_base/BASE_panel.h>
#include <ELE_specific/common.h>

class GUI;
class struct_vulkan;
class Database_sqlite;


class GUI_database : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_database(GUI* gui, bool* show_window, string name);
  ~GUI_database();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void display_option();
  void display_data();

private:
  Database_sqlite* database;

  string path_database;
};

#endif
