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
  void plot_heatmap(utl::base::Plot* utl_plot);
  bool plot_heatmap(utl::base::Plot* utl_plot, utl::base::Axis* x_axis, utl::base::Axis* y_axis);
  void plot_regression(utl::base::Plot* plot);
  void plot_scatter(utl::base::Plot* utl_plot);
  void plot_scatter_rdm();
  void plot_constant_in_time();
  void plot_temperature(float temp_cpu, float temp_gpu);

private:
  utl::implot::Style* implot_style;
};

}
