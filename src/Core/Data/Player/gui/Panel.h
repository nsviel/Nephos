#pragma once

#include <string>

namespace dat::ply{class Node;}
namespace dat::ply::gui{class Player;}
namespace dat::ply::gui{class Info;}
namespace dat::atr::gui{class Panel;}
namespace dat::gph{class Selection;}


namespace dat::ply::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::ply::Node* node_player, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel();

private:
  dat::ply::gui::Player* gui_player;
  dat::ply::gui::Info* gui_info;
  dat::atr::gui::Panel* atr_panel;
  dat::gph::Selection* gph_selection;

  std::string name;
  std::string open_tab = "";
  bool* show_window;
};

}
