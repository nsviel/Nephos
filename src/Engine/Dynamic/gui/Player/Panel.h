#pragma once

#include <string>

namespace dyn{class Node;}
namespace dyn::gui{class Player;}
namespace dyn::gui{class Colorization;}
namespace dyn::gui{class Transformation;}
namespace dyn::gui{class Info;}
namespace dyn::gui{class Configuration;}
namespace dyn::gui{class Normal;}
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
  dyn::gui::Colorization* gui_colorization;
  dyn::gui::Transformation* gui_transformation;
  dyn::gui::Info* gui_information;
  dyn::gui::Configuration* gui_configuration;
  dyn::gui::Normal* gui_normal;
  dat::graph::Selection* dat_selection;

  std::string name;
  std::string open_tab = "";
  bool* show_window;
};

}
