#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}
namespace eng{class Node;}
namespace gui::interface{class Menu;}
namespace dev::gui{class Tab;}


namespace gui::interface{

class Tab
{
public:
  //Constructor / Destructor
  Tab(gui::Node* gui);
  ~Tab();

public:
  //Main functions
  void run_tab();

  //Tab function
  void draw_tab_menu();
  void draw_tab();
  void next_tab();

private:
  eng::Node* node_engine;
  gui::interface::Menu* gui_menu;
  dev::gui::Tab* dev_tab;

  vector<string> vec_tab;
  string active_tab;
  string tab_to_open;
};

}
