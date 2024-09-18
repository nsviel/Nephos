#pragma once

#include <string>

namespace dat::ply{class Node;}
namespace dat::ply::gui{class Player;}
namespace dat::ply::gui{class Info;}
namespace dat::atr::gui{class Color;}
namespace dat::gph{class Selection;}
namespace eng::trf::gui{class Matrix;}


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
  dat::atr::gui::Color* gui_colorization;
  dat::gph::Selection* gph_selection;
  eng::trf::gui::Matrix* gui_transformation;

  std::string name;
  std::string open_tab = "";
  bool* show_window;
};

}
