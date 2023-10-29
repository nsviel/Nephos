#ifndef GUI_TAB_H
#define GUI_TAB_H

#include <Specific/common.h>

class GUI;
class GUI_font;
class GUI_render;
class GUI_dev;
class GUI_render_panel;
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
  void menu_demo();
  void menu_font();
  void menu_git();
  
  //Tab function
  void tabs();
  void draw_panels();
  void next_tab();

  inline GUI_render* get_gui_render(){return gui_render;}
  inline GUI_dev* get_gui_dev(){return gui_dev;}

private:
  GUI* gui;
  GUI_render* gui_render;
  GUI_dev* gui_dev;
  GUI_font* gui_font;
  GUI_git* gui_git;

  vector<string> vec_tab;
  string active_tab;
  string tab_to_open;
  bool show_demo;
};

#endif
