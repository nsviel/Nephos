#ifndef GUI_RENDER_MENU_H
#define GUI_RENDER_MENU_H

#include <UTL_specific/common.h>

class GUI;
class ENG_loader;
class RND_panel;
class RND_init;
class RND_option;
class RND_tab;


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
  RND_panel* rnd_panel;
  RND_option* rnd_option;
  RND_tab* rnd_tab;
};


#endif
