#pragma once

#include <string>

namespace ope{class Node;}
namespace ope::gui{class Color;}
namespace ope::gui{class Transformation;}
namespace ope::gui{class Info;}
namespace ope::gui{class Normal;}
namespace utl::base{class Element;}


namespace ope::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(ope::Node* node_operation);
  ~Panel();

  //Main function
  void design_panel(utl::base::Element* element);

private:
  ope::gui::Color* gui_color;
  ope::gui::Transformation* gui_transformation;
  ope::gui::Info* gui_info;
  ope::gui::Normal* gui_normal;
};

}
