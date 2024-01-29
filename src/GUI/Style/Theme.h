#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}


namespace gui::style{

class Theme
{
public:
  //Constructor / Destructor
  Theme(gui::Node* gui);
  ~Theme();

public:
  //Main functions
  void init_theme();

  //Subfunction
  void color_window();
  void color_widget();

private:

};

}
