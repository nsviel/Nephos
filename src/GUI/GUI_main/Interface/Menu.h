#pragma once

#include <Utility/UTL_specific/common.h>
#include <GUI/GUI_utility/Element/Namespace.h>

class GUI;
class GUI_font;


namespace gui{

class Menu
{
public:
  //Constructor / Destructor
  Menu(GUI* gui);
  ~Menu();

public:
  //Menu function
  void menu();
  void menu_option();
  void menu_demo();
  void menu_git();

private:
  GUI* gui;
  GUI_font* gui_font;
  gui::element::Git* gui_git;

  bool show_demo;
};

}
