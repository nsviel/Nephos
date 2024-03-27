#pragma once

#include <Utility/Specific/common.h>
#include <imgui/implot/implot.h>


namespace utl::implot{

class Style
{
public:
  //Constructor / Destructor
  Style();
  ~Style();

public:
  //Main function
  void make_style();

private:
  bool applied = false;
};

}
