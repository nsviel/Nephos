#pragma once

#include <memory>
#include <string>

namespace dat::atr{class Node;}
namespace dat::atr::gui{class Color;}
namespace dat::atr::gui{class Normal;}
namespace dat::atr{class Field;}
namespace dat::gph{class Selection;}
namespace dat::elm{class Element;}
namespace utl::base{class Element;}


namespace dat::atr::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::atr::Node* node_attribut, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void enum_data(std::shared_ptr<utl::base::Element> element);

private:
  dat::atr::gui::Color* gui_color;
  dat::atr::gui::Normal* gui_normal;
  dat::gph::Selection* gph_selection;
  dat::elm::Element* dat_element;
  dat::atr::Field* atr_field;

  std::string panel_name;
  bool* show_window;
  int item_width;
};

}
