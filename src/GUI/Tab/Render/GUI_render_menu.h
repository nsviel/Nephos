#ifndef GUI_RENDER_MENU_H
#define GUI_RENDER_MENU_H

#include <Specific/common.h>

class GUI;
class Loader;
class Struct_render_panel;
class GUI_init;
class GUI_option;
class GUI_render_panel;


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
  void menu_demo();

private:
  GUI* gui;
  Loader* loaderManager;
  GUI_init* gui_init;
  Struct_render_panel* struct_render_panel;
  GUI_option* gui_option;
  GUI_render_panel* gui_render_panel;

  bool show_demo;

};


#endif
