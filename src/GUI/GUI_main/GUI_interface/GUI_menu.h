#pragma once

#include <UTL_specific/common.h>
#include <GUI_utility/Utility_nsp.h>

class GUI;
class GUI_font;


namespace gui{

class GUI_menu
{
public:
  //Constructor / Destructor
  GUI_menu(GUI* gui);
  ~GUI_menu();

public:
  //Menu function
  void menu();
  void menu_option();
  void menu_demo();
  void menu_git();

private:
  GUI* gui;
  GUI_font* gui_font;
  gui::utility::Git* gui_git;

  bool show_demo;
};

}
