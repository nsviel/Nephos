#pragma once

#include <string>

namespace dat::atr{class Node;}
namespace dat::atr::gui{class Color;}
namespace dat::atr::gui{class Transformation;}
namespace dat::atr::gui{class Info;}
namespace dat::atr::gui{class Operation;}
namespace utl::base{class Element;}


namespace dat::atr::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dat::atr::Node* node_attribut);
  ~Panel();

  //Main function
  void design_panel(utl::base::Element* element);

private:
  dat::atr::gui::Color* gui_color;
  dat::atr::gui::Transformation* gui_transformation;
  dat::atr::gui::Info* gui_info;
  dat::atr::gui::Operation* gui_operation;
};

}
