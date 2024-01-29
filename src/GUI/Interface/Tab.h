#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}
namespace gui::interface{class Menu;}
namespace gui::rnd::tab{class Panel;}
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

  inline gui::rnd::tab::Panel* get_rnd_panel(){return rnd_panel;}
  inline gui::dev::tab::Panel* get_dev_panel(){return dev_panel;}

private:
  gui::Node* gui;
  gui::interface::Menu* gui_menu;
  gui::rnd::tab::Panel* rnd_panel;
  gui::dev::tab::Panel* dev_panel;

  vector<string> vec_tab;
  string active_tab;
  string tab_to_open;
};

}
