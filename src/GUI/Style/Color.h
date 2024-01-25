#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}


namespace gui::style{

class Color
{
public:
  //Constructor / Destructor
  Color(gui::Node* gui);
  ~Color();

public:
  //Main functions
  void apply();
  void color_window();
  void color_widget();

private:

};

}
