#pragma once

#include <Utility/Specific/common.h>

class GUI_font;
class GUI;
class UTL_git;


namespace gui::element{

class Git
{
public:
  //Constructor / Destructor
  Git(GUI* gui);
  ~Git();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void draw_information();
  void draw_branches();

private:
  GUI_font* gui_font;
  UTL_git* git;
};

}
