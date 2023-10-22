#ifndef GUI_TAB_H
#define GUI_TAB_H

#include <Specific/common.h>

class GUI;
class GUI_font;
class GUI_render;
class GUI_dev;
class GUI_render_panel;


class GUI_tab
{
public:
  //Constructor / Destructor
  GUI_tab(GUI* gui);
  ~GUI_tab();

public:
  //Main functions
  void create_panels();
  void run_tab();

  //Subfunction
  void main_menu();
  void menu_demo();
  void menu_font();
  void menu_tabs();
  void draw_panels();

  inline GUI_render* get_gui_render(){return gui_render;}

private:
  GUI* gui;
  GUI_render_panel* gui_render_panel;
  GUI_render* gui_render;
  GUI_dev* gui_dev;
  GUI_font* gui_font;

  string active_tab;
  bool show_demo;
};

#endif
