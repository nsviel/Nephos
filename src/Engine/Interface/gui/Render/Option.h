#pragma once

#include <string>

namespace itf{class Node;}
namespace eng{class Node;}
namespace ctl{class Structure;}
namespace ctl{class Wheel;}
namespace vk::main{class Interface;}


namespace itf::gui{

class Option
{
public:
  //Constructor / Destructor
  Option(itf::Node* node_interface, bool* show_window);
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
