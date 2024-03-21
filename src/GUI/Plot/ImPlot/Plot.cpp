#include "Plot.h"
#include "Namespace.h"

#include <imgui/implot/implot.h>


namespace utl::implot{

Plot::Plot(){
  //---------------------------

  this->implot_style = new utl::implot::Style();

  //---------------------------
}
Plot::~Plot(){}

//Main function
void Plot::plot_scatter_2d(){
  //---------------------------
  implot_style->make_style();

  // Generate random data
  static std::vector<double> x_data, y_data;
  const int num_points = 100;
  if(x_data.size() == 0){
    for (int i = 0; i < num_points; ++i) {
      x_data.push_back((double)i);
      y_data.push_back((double)rand() / RAND_MAX);
    }
  }

  // Create a window
  ImPlot::SetNextAxisLimits(0, num_points, 0, 1);
  if(ImPlot::BeginPlot("Scatter Plot", ImVec2(-1, -1))){
    // Plot the data
    ImPlot::PlotScatter("Random Data", x_data.data(), y_data.data(), num_points);

    // End the plot
    ImPlot::EndPlot();
  }

  //---------------------------
}
void Plot::plot_constant_in_time(){
  //---------------------------

  static vector<float> vec_c;
  static vector<float> vec_d;
  static int cpt = 0;

  cpt++;

  vec_c.push_back(cpt);
  vec_d.push_back(30);

  if(vec_c.size() > 100) vec_c.erase(vec_c.begin());
  if(vec_d.size() > 100) vec_d.erase(vec_d.begin());

  if(ImPlot::BeginPlot("##plot", ImVec2(-1, -1), ImPlotFlags_NoMouseText)){

    ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.5f);
    ImPlot::PushStyleVar(ImPlotStyleVar_PlotMinSize, ImVec2(10, 10));
    ImPlot::PushStyleVar(ImPlotStyleVar_PlotPadding, ImVec2(10, 10));
    ImPlot::PushStyleVar(ImPlotStyleVar_LineWeight, 2);

    ImPlot::PushStyleColor(ImPlotCol_PlotBg, ImVec4(0, 0, 0, 1));
    ImPlot::PushStyleColor(ImPlotCol_AxisBg, ImVec4(0.1, 0.1, 0.1, 1));
        ImPlot::PushStyleColor(ImPlotCol_PlotBorder, ImVec4(0.1, 0.1, 0.1, 1));

    ImPlot::SetupAxisLimitsConstraints(ImAxis_Y1, 0, 60);
    ImPlot::SetupAxisZoomConstraints(ImAxis_Y1, 0, 60);
    ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_NoDecorations, 0);
    ImPlot::SetupAxisLimits(ImAxis_X1, cpt - 100, cpt, ImGuiCond_Always);
    ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 60);

    string value = to_string(vec_d[0]) + " fps";
    ImPlot::PlotText(value.c_str(), cpt - 10, vec_d[0] + 5);
    ImPlot::PlotLine("", vec_c.data(), vec_d.data(), vec_d.size());
    ImPlot::PlotShaded("", vec_c.data(), vec_d.data(), vec_d.size(), -INFINITY, 0);

    ImPlot::PopStyleVar(4);
    ImPlot::PopStyleColor();

    ImPlot::EndPlot();
  }

  //---------------------------
}

}
