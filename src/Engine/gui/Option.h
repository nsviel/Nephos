#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace vk::main{class Info;}


namespace eng::gui{

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
  void option_fps();

private:
  vk::main::Info* vk_info;

  int width;
  string name;
  bool* show_window;
};

}
