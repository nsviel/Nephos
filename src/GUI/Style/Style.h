#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}


namespace gui{

class Style
{
public:
  //Constructor / Destructor
  Style(gui::Node* gui);
  ~Style();

public:
  //Main function
  void gui_style();

  //Subfunction
  void style_window();

private:
};

}
