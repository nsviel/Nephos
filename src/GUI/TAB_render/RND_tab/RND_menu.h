#pragma once

#include <UTL_specific/common.h>
#include <TAB_render/Tab_nsp.h>

class GUI;
class ENG_loader;
class RND_init;

namespace gui::rnd::tab{
class RND_panel;
class RND_option;
class Tab;


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
  gui::rnd::tab::RND_panel* rnd_panel;
  gui::rnd::tab::RND_option* rnd_option;
  gui::rnd::tab::Tab* rnd_tab;
};

}
