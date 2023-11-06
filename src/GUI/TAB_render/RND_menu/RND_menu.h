#ifndef GUI_RENDER_MENU_H
#define GUI_RENDER_MENU_H

#include <ELE_specific/common.h>

class GUI;
class ENG_loader;
class RND_panel;
class RND_init;
class RND_option;
class TAB_render;


class RND_menu
{
public:
  //Constructor / Destructor
  RND_menu(GUI* gui);
  ~RND_menu();

public:
  //Main function
  void run_tab_menu();

  //Subfunctions

private:
  GUI* gui;
  ENG_loader* eng_loader;
  RND_init* gui_init;
  RND_panel* gui_render_panel;
  RND_option* gui_render_option;
  TAB_render* gui_tab_render;

  bool show_demo;

};


#endif
