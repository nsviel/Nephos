#ifndef GUI_DATABASE_H
#define GUI_DATABASE_H

#include <Panel/BASE_panel.h>
#include <Specific/common.h>

class GUI;
class VK_struct;
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
  void design_database();
  void display_option();
  void display_data();

private:
  Database_sqlite* database;

  string path_database;
};

#endif
