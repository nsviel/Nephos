#ifndef GUI_DEV_PANEL_H
#define GUI_DEV_PANEL_H

#include <Specific/common.h>

class GUI;
class GUI_code_editor;
class GUI_dev_panel;
class GUI_dev_command;


class GUI_dev
{
public:
  //Constructor / Destructor
  GUI_dev(GUI* gui);
  ~GUI_dev();

public:
  //Main functions
  void create_panels();
  void draw_panels();
  void open_panels();

  inline GUI_dev_panel* get_render_panel(){return gui_dev_panel;}

private:
  GUI* gui;
  GUI_dev_panel* gui_dev_panel;
  GUI_dev_command* gui_dev_command;
  vector<GUI_code_editor*> vec_editor;
};

#endif
