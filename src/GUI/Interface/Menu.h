#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Namespace.h>

namespace gui{class Node;}
class GUI_font;


namespace gui{

class Menu
{
public:
  //Constructor / Destructor
  Menu(gui::Node* gui);
  ~Menu();

public:
  //Menu function
  void menu();
  void menu_option();
  void menu_demo();
  void menu_git();

private:
  gui::Node* gui;
  GUI_font* gui_font;
  utl::element::gui::Git* gui_git;

  bool show_demo;
};

}
