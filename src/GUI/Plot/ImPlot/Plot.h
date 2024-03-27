#pragma once

#include <Utility/Specific/common.h>

namespace utl::implot{class Style;}


namespace utl::implot{

class Plot
{
public:
  //Constructor / Destructor
  Plot();
  ~Plot();

public:
  //Main function
  void plot_scatter_2d(std::vector<float>& x, std::vector<float>& y, float height, string title);
  void plot_scatter_2d_last_pt_highlighted(std::vector<float>& x, std::vector<float>& y, float height, string title);
  void plot_scatter_2d_rdm();
  void plot_constant_in_time();

private:
  utl::implot::Style* implot_style;
};

}
