#ifndef GUI_MENUBAR_H
#define GUI_MENUBAR_H

#include <Specific/common.h>

class GUI;
class Loader;
class Panel;
class GUI_init;
class GUI_option;
class GUI_panel_engine;


class GUI_mainmenubar
{
public:
  //Constructor / Destructor
  GUI_mainmenubar(GUI* gui);
  ~GUI_mainmenubar();

public:
  //Main function
  void design_menubar();

  //Subfunctions
  void menu();
  void menu_demo();
  void main_tab();

private:
  GUI* gui;
  Loader* loaderManager;
  GUI_init* gui_init;
  Panel* panel;
  GUI_option* gui_option;
  GUI_panel_engine* gui_panel_engine;

  bool show_demo;

};


#endif
