#pragma once

#include <Utility/Specific/common.h>
#include <GUI/TAB_render/Tab/Namespace.h>

class GUI;

namespace gui::rnd::tab{
class Loader;


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
  gui::rnd::tab::Init* rnd_init;
  gui::rnd::tab::Panel* rnd_panel;
  gui::rnd::tab::Option* rnd_option;
};

}
