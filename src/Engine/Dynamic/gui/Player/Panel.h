#pragma once

#include <string>

namespace dyn{class Node;}
namespace dyn::gui{class Operation;}
namespace dyn::gui{class Player;}


namespace dyn::gui{

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
  dyn::gui::Operation* gui_operation;

  std::string name;
  std::string open_tab = "";
  bool* show_window;
};

}
