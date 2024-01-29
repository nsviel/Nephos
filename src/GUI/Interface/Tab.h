#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}
namespace gui::interface{class Menu;}
namespace eng::gui{class Tab;}
namespace gui::dev::tab{class Panel;}


namespace gui::interface{

class Tab
{
public:
  //Constructor / Destructor
  Tab(gui::Node* gui);
  ~Tab();

public:
  //Main functions
  void init_tab();
  void run_tab();

  //Tab function
  void draw_tab_menu();
  void draw_tab();
  void next_tab();

private:
  gui::Node* gui;
  gui::interface::Menu* gui_menu;
  eng::gui::Tab* eng_tab;
  gui::dev::tab::Panel* dev_tab;

  vector<string> vec_tab;
  string active_tab;
  string tab_to_open;
};

}
