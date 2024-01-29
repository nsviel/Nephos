#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}
namespace gui::style{class Theme;}


namespace gui{

class Style
{
public:
  //Constructor / Destructor
  Style(gui::Node* gui);
  ~Style();

public:
  //Main function
  void init_style();

  //Subfunction
  void style_window();

private:
};

}
