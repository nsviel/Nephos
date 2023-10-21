#ifndef GUI_TAB_H
#define GUI_TAB_H

#include <Specific/common.h>

class GUI;
class GUI_panel_engine;
class Panel_engine;


class GUI_tab
{
public:
  //Constructor / Destructor
  GUI_tab(GUI* gui);
  ~GUI_tab();

public:
  //Main functions

  inline GUI_panel_engine* get_gui_panel_engine(){return gui_panel_engine;}
  
private:
  GUI* gui;
  Panel_engine* panel;
  GUI_panel_engine* gui_panel_engine;
};

#endif
