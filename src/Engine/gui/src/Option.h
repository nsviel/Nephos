#pragma once

#include <Utility/Specific/common.h>

namespace eng::gui{class Node;}
namespace eng::ope{class Wheel;}
namespace vk::main{class Info;}


namespace eng::gui{

class Option
{
public:
  //Constructor / Destructor
  Option(eng::gui::Node* node_gui, bool* show_window);
  ~Option();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunctions
  void option_color();
  void option_wheel();

private:
  eng::ope::Wheel* ope_wheel;
  vk::main::Info* vk_info;

  int width;
  string name;
  bool* show_window;
};

}
