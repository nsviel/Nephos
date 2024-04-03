#pragma once

#include <Utility/Specific/Common.h>

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
  void plot_heatmap(utl::type::Plot* utl_plot);
  bool plot_heatmap(utl::type::Plot* utl_plot, utl::type::Axis* x_axis, utl::type::Axis* y_axis);
  void plot_regression(utl::type::Plot* plot);
  void plot_scatter(utl::type::Plot* utl_plot);
  void plot_scatter_rdm();
  void plot_constant_in_time();

private:
  utl::implot::Style* implot_style;
};

}
