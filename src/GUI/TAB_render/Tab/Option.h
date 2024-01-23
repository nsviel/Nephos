#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Base/GUI/Panel.h>

class GUI;
class VK_info;


namespace gui::rnd::tab{

class Option : public utl::base::Panel
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
