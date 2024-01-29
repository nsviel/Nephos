#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}


namespace gui::style{

class Config
{
public:
  //Constructor / Destructor
  Config(gui::Node* gui);
  ~Config();

public:
  //Main function
  void init_style();

  //Subfunction
  void style_window();

private:
};

}
