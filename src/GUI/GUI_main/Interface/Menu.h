#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>
#include <Utility/Element/Git/gui/Git.h>

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
