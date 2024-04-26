#pragma once

#include <Utility/Specific/Common.h>

namespace eng{class Node;}
namespace ope{class Wheel;}
namespace vk::main{class Interface;}


namespace rnd::gui{

class Option
{
public:
  //Constructor / Destructor
  Option(eng::Node* node_engine, bool* show_window);
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
