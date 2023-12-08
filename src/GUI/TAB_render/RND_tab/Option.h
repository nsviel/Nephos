#pragma once

#include <UTL_specific/common.h>
#include <GUI_base/BASE_panel.h>

class GUI;
class VK_info;


namespace gui::rnd::tab{

class Option : public BASE_panel
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
