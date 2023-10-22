#ifndef GUI_RENDER_MENU_H
#define GUI_RENDER_MENU_H

#include <Specific/common.h>

class GUI;
class Loader;
class GUI_render_panel;
class GUI_init;
class GUI_render_option;
class GUI_render;


class GUI_render_menu
{
public:
  //Constructor / Destructor
  GUI_render_menu(GUI* gui);
  ~GUI_render_menu();

public:
  //Main function
  void design_menubar();

  //Subfunctions
  void menu();

private:
  GUI* gui;
  Loader* loaderManager;
  GUI_init* gui_init;
  GUI_render_panel* gui_render_panel;
  GUI_render_option* gui_render_option;
  GUI_render* gui_render;

  bool show_demo;

};


#endif
