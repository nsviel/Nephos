#pragma once

#include <Utility/Specific/Common.h>

namespace gui{class Node;}
namespace eng{class Node;}
namespace sce{class Node;}
namespace prf{class Node;}

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
  prf::Node* node_profiler;

  gui::interface::Menu* gui_menu;
  gui::tab::dev::Menu* dev_menu;
  gui::tab::eng::Menu* eng_menu;

  vector<string> vec_tab;
  string active_tab;
  string tab_to_open;
};

}
