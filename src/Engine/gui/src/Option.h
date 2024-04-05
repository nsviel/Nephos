#pragma once

#include <Utility/Specific/Common.h>

namespace eng::gui{class Node;}
namespace ope{class Wheel;}
namespace vk::main{class Interface;}


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
  ope::Wheel* ope_wheel;
  vk::main::Interface* vk_interface;

  int width;
  string name;
  bool* show_window;
};

}
