#pragma once

#include <memory>
#include <string>

namespace dat::atr{class Node;}
namespace dat::atr::gui{class Color;}
namespace dat::atr::gui{class Normal;}
namespace dat::gph{class Selection;}


namespace dat::atr::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::atr::Node* node_attribut, bool* show_window);
  ~Panel();

  //Main function
  void run_panel();
  void design_panel();

private:
  dat::atr::gui::Color* gui_color;
  dat::atr::gui::Normal* gui_normal;
  dat::gph::Selection* gph_selection;

  std::string panel_name;
  bool* show_window;
  int item_width;
};

}
