#pragma once

#include <TAB_dev/Tab/Namespace.h>
#include <TAB_render/Tab/Namespace.h>
#include <GUI_main/GUI_nsp.h>
#include <UTL_specific/common.h>

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

  inline gui::rnd::tab::Tab* get_rnd_tab(){return rnd_tab;}
  inline gui::dev::tab::Tab* get_dev_tab(){return dev_tab;}

private:
  GUI* gui;
  gui::Menu* gui_menu;
  gui::rnd::tab::Tab* rnd_tab;
  gui::dev::tab::Tab* dev_tab;

  vector<string> vec_tab;
  string active_tab;
  string tab_to_open;
};

}
