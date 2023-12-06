#ifndef DEV_TAB_H
#define DEV_TAB_H

#include <UTL_specific/common.h>

class GUI;
class DEV_code_editor;
class DEV_panel;
class DEV_command;
class GUI_database;


class DEV_tab
{
public:
  //Constructor / Destructor
  DEV_tab(GUI* gui);
  ~DEV_tab();

public:
  //Main functions
  void create_panels();
  void draw_panels();
  void open_panels();

  inline DEV_panel* get_dev_panel(){return gui_dev_panel;}

private:
  GUI* gui;
  DEV_panel* gui_dev_panel;
  DEV_command* gui_dev_command;
  GUI_database* gui_database;
};

#endif
