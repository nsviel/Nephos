#pragma once

#include <Utility/UTL_specific/common.h>

class GUI;


namespace gui{

class Style
{
public:
  //Constructor / Destructor
  Style(GUI* gui);
  ~Style();

public:
  //Main function
  void gui_style();

  //Subfunction
  void style_window();
  void color_window();
  void color_widget();

private:
};

}
