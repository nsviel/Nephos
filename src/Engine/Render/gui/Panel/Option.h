#pragma once

#include <string>

namespace rnd{class Node;}
namespace eng{class Node;}
namespace rnd::gui{class Control;}
namespace vk::main{class Interface;}


namespace rnd::gui{

class Option
{
public:
  //Constructor / Destructor
  Option(rnd::Node* node_render, bool* show_window);
  ~Option();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunctions
  void option_color();
  void option_wheel();

private:
  rnd::gui::Control* gui_control;
  vk::main::Interface* vk_interface;

  std::string name;
  int width;
  bool* show_window;
};

}
