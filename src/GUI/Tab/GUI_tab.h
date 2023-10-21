#ifndef GUI_TAB_H
#define GUI_TAB_H

#include <Specific/common.h>

class GUI;
class Panel_engine;


class GUI_tab
{
public:
  //Constructor / Destructor
  GUI_tab(GUI* gui);
  ~GUI_tab();

public:
  //Main functions

private:
  GUI* gui;
  Panel_engine* panel;

};

#endif
