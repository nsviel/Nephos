#ifndef GUI_TAB_H
#define GUI_TAB_H

#include <UTL_specific/common.h>

class GUI;
class GUI_menu;
class RND_tab;
class DEV_tab;


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

  inline RND_tab* get_rnd_tab(){return rnd_tab;}
  inline DEV_tab* get_dev_tab(){return dev_tab;}

private:
  GUI* gui;
  GUI_menu* gui_menu;
  RND_tab* rnd_tab;
  DEV_tab* dev_tab;

  vector<string> vec_tab;
  string active_tab;
  string tab_to_open;
};

#endif
