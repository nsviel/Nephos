#pragma once

namespace gui{class Node;}
namespace gui::style{class Font;}
namespace gui::state{class Manager;}
namespace gui::interface{class Demo;}
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

  //Subfunction
  void menu_demo();
  void menu_state();

private:
  gui::style::Font* gui_font;
  gui::interface::Demo* gui_demo;
  gui::state::Manager* gui_state;
  utl::element::gui::Git* gui_git;
};

}
