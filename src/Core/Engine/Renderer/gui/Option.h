#pragma once

#include <string>

namespace rnd{class Node;}
namespace core{class Node;}
namespace ctl{class Structure;}
namespace ctl{class Wheel;}
namespace vk::main{class Interface;}


namespace rnd::gui{

class Option
{
public:
  //Constructor / Destructor
  Option(rnd::Node* node_renderer, bool* show_window);
  ~Option();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunctions
  void option_color();
  void option_wheel();
  void visualization_mode();

private:
  ctl::Structure* ctl_struct;
  ctl::Wheel* ctl_wheel;
  vk::main::Interface* vk_interface;

  std::string name;
  int width;
  bool* show_window;
};

}
