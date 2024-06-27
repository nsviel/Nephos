#pragma once

namespace gui{class Node;}
namespace gui::style{class Font;}
namespace gui::interface{class Docking;}
namespace utl::element::gui{class Git;}


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
  void menu_imgui();
  void menu_git();

private:
  gui::Node* gui;
  gui::style::Font* gui_font;
  gui::interface::Docking* gui_docking;
  utl::element::gui::Git* gui_git;

  bool show_demo;
};

}
