#pragma once

#include <vector>
#include <string>

namespace gui{class Node;}
namespace core{class Node;}
namespace sce{class Node;}

namespace gui::menu{class Left;}
namespace gui::menu{class Center;}


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
  void draw_tab_menu();
  void draw_tab();

private:
  core::Node* node_core;
  sce::Node* node_scene;

  gui::menu::Left* menu_left;
  gui::menu::Center* menu_center;
};

}
