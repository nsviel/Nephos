#pragma once

#include <string>

namespace dyn{class Node;}
namespace dyn::gui{class Player;}
namespace dyn::gui{class Configuration;}
namespace dat::graph{class Selection;}
namespace ope::gui{class Panel;}


namespace dyn::gui::player{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dyn::Node* node_dynamic, bool* show_window);
  ~Panel();

  //Main function
  void run_panel();
  void design_panel();

private:
  dyn::gui::Player* gui_player;
  dyn::gui::Configuration* gui_configuration;
  dat::graph::Selection* dat_selection;
  ope::gui::Panel* ope_panel;

  std::string name;
  std::string open_tab = "";
  bool* show_window;
};

}
