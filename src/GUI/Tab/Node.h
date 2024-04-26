#pragma once

#include <Utility/Specific/Common.h>

namespace gui{class Node;}
namespace eng{class Node;}
namespace gui::interface{class Menu;}
namespace dev::gui{class Tab;}
namespace eng::gui{class Node;}


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
  void run_tab();

  //Tab function
  void draw_tab_menu();
  void draw_tab();
  void next_tab();

private:
  eng::Node* node_engine;
  gui::interface::Menu* gui_menu;
  dev::gui::Tab* dev_tab;
  eng::gui::Node* tab_engine;

  vector<string> vec_tab;
  string active_tab;
  string tab_to_open;
};

}
