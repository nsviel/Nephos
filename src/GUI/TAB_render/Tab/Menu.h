#pragma once

#include <Utility/Specific/common.h>
#include <GUI/TAB_render/Tab/Namespace.h>

namespace gui::rnd::tab{
class Panel;


class Menu
{
public:
  //Constructor / Destructor
  Menu(gui::rnd::tab::Panel* rnd_panel);
  ~Menu();

public:
  //Main function
  void run_tab_menu();

  //Subfunctions
  void loader_dialog();
  void loader_panel();

private:
  gui::rnd::tab::Panel* rnd_panel;
};

}
