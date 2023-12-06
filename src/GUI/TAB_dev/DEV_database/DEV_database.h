#ifndef GUI_DATABASE_H
#define GUI_DATABASE_H

#include <GUI_base/BASE_panel.h>
#include <UTL_specific/common.h>

class GUI;
class Struct_vulkan;
class UTL_database;


namespace dev{

class DEV_database : public BASE_panel
{
public:
  //Constructor / Destructor
  DEV_database(GUI* gui, bool* show_window, string name);
  ~DEV_database();

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


#endif
