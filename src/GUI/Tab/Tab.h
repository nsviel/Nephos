#pragma once

#include <GUI/Namespace.h>
#include <GUI/Namespace.h>
#include <GUI/Namespace.h>
#include <Utility/Specific/common.h>

namespace gui{class Node;}
namespace gui{class Menu;}
namespace gui::rnd::tab{class Panel;}
namespace gui::dev::tab{class Panel;}


namespace gui{

class Tab
{
public:
  //Constructor / Destructor
  Tab(gui::Node* gui);
  ~Tab();

public:
  //Main functions
  void create_panels();
  void run_tab();

  //Tab function
  void tabs();
  void draw_panels();
  void next_tab();

  inline gui::rnd::tab::Panel* get_rnd_panel(){return rnd_panel;}
  inline gui::dev::tab::Panel* get_dev_panel(){return dev_panel;}

private:
  gui::Node* gui;
  gui::Menu* gui_menu;
  gui::rnd::tab::Panel* rnd_panel;
  gui::dev::tab::Panel* dev_panel;

  vector<string> vec_tab;
  string active_tab;
  string tab_to_open;
};

}
