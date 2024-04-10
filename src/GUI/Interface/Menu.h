#pragma once

#include <Utility/Specific/Common.h>

namespace utl::element::gui{class Git;}
namespace gui{class Node;}
namespace gui::style{class Font;}


namespace gui::interface{

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
  utl::element::gui::Git* gui_git;
  gui::Node* gui;
  gui::style::Font* gui_font;

  bool show_demo;
};

}
