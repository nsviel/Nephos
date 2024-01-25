#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}
class VK_info;


namespace gui::rnd::tab{

class Option
{
public:
  //Constructor / Destructor
  Option(gui::Node* gui, bool* show_window, string name);
  ~Option();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunctions
  void option_color();
  void option_fps();

private:
  gui::Node* gui;
  VK_info* vk_info;

  int width;
  string name;
  bool* show_window;
};

}
