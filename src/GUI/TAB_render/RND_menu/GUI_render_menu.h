#ifndef GUI_RENDER_MENU_H
#define GUI_RENDER_MENU_H

#include <Specific/common.h>

class GUI;
class Loader;
class RND_panel;
class GUI_init;
class GUI_render_option;
class TAB_render;


class GUI_render_menu
{
public:
  //Constructor / Destructor
  GUI_render_menu(GUI* gui);
  ~GUI_render_menu();

public:
  //Main function
  void run_tab_menu();

  //Subfunctions

private:
  GUI* gui;
  Loader* loaderManager;
  GUI_init* gui_init;
  RND_panel* gui_render_panel;
  GUI_render_option* gui_render_option;
  TAB_render* gui_tab_render;

  bool show_demo;

};


#endif
