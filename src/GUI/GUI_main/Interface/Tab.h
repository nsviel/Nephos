#pragma once

#include <GUI/TAB_dev/Tab/Namespace.h>
#include <GUI/TAB_render/Tab/Namespace.h>
#include <GUI/GUI_main/Namespace.h>
#include <Utility/Specific/common.h>

class GUI;


namespace gui{

class Tab
{
public:
  //Constructor / Destructor
  Tab(GUI* gui);
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
  GUI* gui;
  gui::Menu* gui_menu;
  gui::rnd::tab::Panel* rnd_panel;
  gui::dev::tab::Panel* dev_panel;

  vector<string> vec_tab;
  string active_tab;
  string tab_to_open;
};

}
