#pragma once

#include <UTL_specific/common.h>
#include <GUI/GUI_utility/Base/Namespace.h>

class GUI;
class VK_info;


namespace gui::rnd::tab{

class Option : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Option(GUI* gui, bool* show_window, string name);
  ~Option();

public:
  //Main function
  void design_panel();

  //Subfunctions
  void option_color();
  void option_fps();

private:
  GUI* gui;
  VK_info* vk_info;

  int width;
};

}
