#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}
namespace gui::style{class GUI_font;}
namespace utl::element::gui{class Git;}


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
  gui::style::GUI_font* gui_font;
  utl::element::gui::Git* gui_git;

  bool show_demo;
};

}
