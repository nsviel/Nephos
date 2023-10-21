#ifndef GUI_TAB_H
#define GUI_TAB_H

#include <Specific/common.h>

class GUI;
class GUI_render_panel;
class GUI_dev_panel;
class Struct_render_panel;


class GUI_tab
{
public:
  //Constructor / Destructor
  GUI_tab(GUI* gui);
  ~GUI_tab();

public:
  //Main functions
  void create_panels();
  void draw_tabs();
  void menu_demo();

  inline GUI_render_panel* get_gui_render_panel(){return gui_render_panel;}

private:
  GUI* gui;
  Struct_render_panel* struct_render_panel;
  GUI_render_panel* gui_render_panel;
  GUI_dev_panel* gui_dev_panel;

  string active_tab;
  bool show_demo;
};

#endif
