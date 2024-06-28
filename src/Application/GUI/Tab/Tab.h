#pragma once

#include <vector>
#include <string>

namespace gui{class Node;}
namespace eng{class Node;}
namespace sce{class Node;}

namespace gui::interface{class Menu;}
namespace gui::tab::dev{class Menu;}
namespace gui::tab::eng{class Menu;}


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
  void next_tab();

private:
  eng::Node* node_engine;
  sce::Node* node_scene;

  gui::interface::Menu* gui_menu;
  gui::tab::dev::Menu* dev_menu;
  gui::tab::eng::Menu* eng_menu;

  std::vector<std::string> vec_tab;
  std::string active_tab;
  std::string tab_to_open;
};

}
