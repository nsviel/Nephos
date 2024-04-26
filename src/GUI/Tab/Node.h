#pragma once

#include <Utility/Specific/Common.h>

namespace gui{class Node;}
namespace eng{class Node;}
namespace gui::interface{class Menu;}
namespace gui::tab::dev{class Menu;}
namespace gui::tab::eng{class Menu;}
namespace engine = eng;


namespace gui::tab{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(gui::Node* gui);
  ~Node();

public:
  //Main function
  void loop();

  //Tab function
  void draw_tab_menu();
  void draw_tab();
  void next_tab();

private:
  engine::Node* node_engine;
  gui::interface::Menu* gui_menu;
  gui::tab::dev::Menu* dev_menu;
  gui::tab::eng::Menu* eng_menu;

  vector<string> vec_tab;
  string active_tab;
  string tab_to_open;
};

}
