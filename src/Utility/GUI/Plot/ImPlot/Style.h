#pragma once

#include <Utility/Specific/Common.h>
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

  //Subfunction
  void make_style_parameter();
  void make_custom_colormap();

  inline ImPlotColormap get_colormap_heatmap(){return heatmap;}

private:
  ImPlotColormap heatmap = -1;
  bool applied = false;
};

}
