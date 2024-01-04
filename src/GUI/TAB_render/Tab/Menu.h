#pragma once

#include <Utility/Specific/common.h>
#include <GUI/TAB_render/Tab/Namespace.h>
#include <Engine/Data/Namespace.h>

class GUI;

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
  void loader_dialog();
  void loader_panel();

private:
  GUI* gui;
  eng::data::Loader* eng_loader;
  Init* gui_init;
  gui::rnd::tab::Panel* rnd_panel;
  gui::rnd::tab::Option* rnd_option;
  gui::rnd::tab::Tab* rnd_tab;
};

}
