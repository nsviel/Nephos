#pragma once

namespace gui{class Node;}
namespace gui::style{class Font;}
namespace gui::state{class Manager;}
namespace gui::menu{class Demo;}


namespace gui::menu{

class Left
{
public:
  //Constructor / Destructor
  Left(gui::Node* node_gui);
  ~Left();

public:
  //Menu function
  void draw();

  //Subfunction
  void menu_font();
  void menu_imgui();

private:
  gui::style::Font* gui_font;
  gui::menu::Demo* gui_demo;
  gui::state::Manager* gui_state;
};

}
