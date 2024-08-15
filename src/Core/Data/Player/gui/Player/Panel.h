#pragma once

#include <string>

namespace dat::ply{class Node;}
namespace dat::ply::gui{class Player;}
namespace dat::ply::gui{class Configuration;}
namespace dat::gph{class Selection;}
namespace dat::atr::gui{class Panel;}


namespace dat::ply::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::ply::Node* node_player, bool* show_window);
  ~Panel();

  //Main function
  void run_panel();
  void design_panel();

private:
  dat::ply::gui::Player* gui_player;
  dat::ply::gui::Configuration* gui_configuration;
  dat::gph::Selection* dat_selection;
  dat::atr::gui::Panel* atr_panel;

  std::string name;
  std::string open_tab = "";
  bool* show_window;
};

}
