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
  Menu(gui::Node* node_gui);
  ~Menu();

public:
  //Menu function
  void menu();

  //Subfunction
  void menu_font();
  void menu_imgui();
  void menu_git();

private:
  gui::style::Font* gui_font;
  gui::interface::Demo* gui_demo;
  gui::state::Manager* gui_state;
  utl::element::gui::Git* gui_git;
};

}
