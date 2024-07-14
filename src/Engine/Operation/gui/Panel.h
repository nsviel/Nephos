#pragma once

#include <string>

namespace dyn{class Node;}
namespace ope::gui{class Colorization;}
namespace ope::gui{class Transformation;}
namespace ope::gui{class Info;}
namespace ope::gui{class Configuration;}
namespace ope::gui{class Normal;}
namespace utl::base{class Element;}


namespace ope::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(dyn::Node* node_dynamic, bool* show_window);
  ~Panel();

  //Main function
  void design_panel(utl::base::Element* element);

private:
  ope::gui::Colorization* gui_colorization;
  ope::gui::Transformation* gui_transformation;
  ope::gui::Info* gui_info;
  ope::gui::Configuration* gui_configuration;
  ope::gui::Normal* gui_normal;
};

}
