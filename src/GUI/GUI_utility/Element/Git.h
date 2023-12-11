#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>

class GUI_font;
class GUI;


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
  util::element::Git* git;
};

}
