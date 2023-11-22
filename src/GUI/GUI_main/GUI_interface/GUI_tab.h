#ifndef GUI_TAB_H
#define GUI_TAB_H

#include <UTL_specific/common.h>

class GUI;
class GUI_menu;
class TAB_render;
class TAB_dev;


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

  //Tab function
  void tabs();
  void draw_panels();
  void next_tab();

  inline TAB_render* get_gui_render(){return gui_tab_render;}
  inline TAB_dev* get_gui_dev(){return gui_tab_dev;}

private:
  GUI* gui;
  GUI_menu* gui_menu;
  TAB_render* gui_tab_render;
  TAB_dev* gui_tab_dev;

  vector<string> vec_tab;
  string active_tab;
  string tab_to_open;
};

#endif
