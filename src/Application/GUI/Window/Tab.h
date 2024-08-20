#pragma once

#include <vector>
#include <string>

namespace gui{class Node;}
namespace core{class Node;}

namespace gui{class Docking;}
namespace gui::state{class Manager;}
namespace gui::menu{class Left;}
namespace gui::menu{class Center;}
namespace gui::menu{class Demo;}


namespace gui{

class Tab
{
public:
  //Constructor / Destructor
  Tab(gui::Node* node_gui);
  ~Tab();

public:
  //Main function
  void loop();

  //Tab function
  void draw_frame();
  void draw_menu();
  void draw_tab();

private:
  core::Node* node_core;

  gui::Docking* gui_docking;
  gui::state::Manager* gui_state;
  gui::menu::Demo* gui_demo;
  gui::menu::Left* menu_left;
  gui::menu::Center* menu_center;
};

}
