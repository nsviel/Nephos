#pragma once

#include <string>

namespace dyn{class Node;}
namespace dyn::gui{class Player;}
namespace ope::gui{class Colorization;}
namespace ope::gui{class Transformation;}
namespace ope::gui{class Info;}
namespace dyn::gui{class Configuration;}
namespace ope::gui{class Normal;}
namespace dat::graph{class Selection;}


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
  ope::gui::Colorization* gui_colorization;
  ope::gui::Transformation* gui_transformation;
  ope::gui::Info* gui_information;
  dyn::gui::Configuration* gui_configuration;
  ope::gui::Normal* gui_normal;
  dat::graph::Selection* dat_selection;

  std::string name;
  std::string open_tab = "";
  bool* show_window;
};

}
