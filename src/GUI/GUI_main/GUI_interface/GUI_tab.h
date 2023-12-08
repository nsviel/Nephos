#ifndef GUI_TAB_H
#define GUI_TAB_H

#include <TAB_dev/Tab_nsp.h>
#include <TAB_render/Tab_nsp.h>
#include <UTL_specific/common.h>

class GUI;
class GUI_menu;


class GUI_tab
{
public:
  //Constructor / Destructor
  GUI_tab(GUI* gui);
  ~GUI_tab();

public:
  //Main functions
  void create_panels();
  void run_tab();

  //Tab function
  void tabs();
  void draw_panels();
  void next_tab();

  inline gui::rnd::tab::RND_tab* get_rnd_tab(){return rnd_tab;}
  inline gui::dev::tab::Tab* get_dev_tab(){return dev_tab;}

private:
  GUI* gui;
  GUI_menu* gui_menu;
  gui::rnd::tab::RND_tab* rnd_tab;
  gui::dev::tab::Tab* dev_tab;

  vector<string> vec_tab;
  string active_tab;
  string tab_to_open;
};

#endif
