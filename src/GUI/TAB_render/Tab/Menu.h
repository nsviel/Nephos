#pragma once

#include <UTL_specific/common.h>
#include <TAB_render/Tab/Namespace.h>

class GUI;
class ENG_loader;
class Init;

namespace gui::rnd::tab{
class Panel;
class Option;
class Tab;


class Menu
{
public:
  //Constructor / Destructor
  Menu(GUI* gui);
  ~Menu();

public:
  //Main function
  void run_tab_menu();

  //Subfunctions

private:
  GUI* gui;
  ENG_loader* eng_loader;
  Init* gui_init;
  gui::rnd::tab::Panel* rnd_panel;
  gui::rnd::tab::Option* rnd_option;
  gui::rnd::tab::Tab* rnd_tab;
};

}
