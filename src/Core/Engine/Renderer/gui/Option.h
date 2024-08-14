#pragma once

#include <string>

namespace rnd{class Node;}
namespace core{class Node;}
namespace ctr{class Structure;}
namespace ctr{class Wheel;}
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
  ctr::Structure* ctr_struct;
  ctr::Wheel* ctr_wheel;
  vk::main::Interface* vk_interface;

  std::string name;
  int width;
  bool* show_window;
};

}
