#ifndef GUI_TAB_H
#define GUI_TAB_H

#include <UTL_specific/common.h>

class GUI;
class GUI_font;
class TAB_render;
class TAB_dev;
class RND_panel;
class GUI_git;


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

  //Menu function
  void menu();
  void menu_option();
  void menu_demo();
  void menu_git();

  //Tab function
  void tabs();
  void draw_panels();
  void next_tab();

  inline TAB_render* get_gui_render(){return gui_tab_render;}
  inline TAB_dev* get_gui_dev(){return gui_tab_dev;}

private:
  GUI* gui;
  TAB_render* gui_tab_render;
  TAB_dev* gui_tab_dev;
  GUI_font* gui_font;
  GUI_git* gui_git;

  vector<string> vec_tab;
  string active_tab;
  string tab_to_open;
  bool show_demo;
};

#endif
