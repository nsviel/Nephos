#ifndef GUI_DEV_PANEL_H
#define GUI_DEV_PANEL_H

#include <UTL_specific/common.h>

class GUI;
class DEV_code_editor;
class DEV_panel;
class DEV_command;


class TAB_dev
{
public:
  //Constructor / Destructor
  TAB_dev(GUI* gui);
  ~TAB_dev();

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

};

#endif
