#pragma once

#include <vector>
#include <string>

namespace gui{class Node;}

namespace gui{class Docking;}
namespace gui::state{class Manager;}
namespace gui::menu{class Left;}
namespace gui::menu{class Center;}
namespace gui::menu{class Demo;}


namespace gui{

class Layout
{
public:
  //Constructor / Destructor
  Layout(gui::Node* node_gui);
  ~Layout();

public:
  //Main function
  void loop();

  //Subfunction
  void draw_frame();
  void draw_menu();
  void draw_panel();

private:
  gui::Node* node_gui;

  gui::Docking* gui_docking;
  gui::state::Manager* gui_state;
  gui::menu::Demo* gui_demo;
  gui::menu::Left* menu_left;
  gui::menu::Center* menu_center;
};

}