#pragma once

namespace gui{class Node;}
namespace gui{class Structure;}
namespace gui::style{class Font;}
namespace gui::interface{class State;}
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
  gui::Structure* gui_struct;
  gui::style::Font* gui_font;
  gui::interface::State* gui_state;
  utl::element::gui::Git* gui_git;
};

}
