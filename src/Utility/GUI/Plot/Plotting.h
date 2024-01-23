#pragma once

#include <Utility/Specific/common.h>
#include <imgui/implot/implot.h>


namespace gui::plot{

class Plotting
{
public:
  //Constructor / Destructor
  Plotting();
  ~Plotting();

public:
  //Main function
  void plot_constant_in_time();

  //Subfunction
  void implot_style();

private:
};

}
