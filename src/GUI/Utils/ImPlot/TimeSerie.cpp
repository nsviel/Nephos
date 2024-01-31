#include "TimeSerie.h"

#include <imgui/implot/implot.h>


namespace utl::gui::plot{

TimeSerie::TimeSerie(){
  //---------------------------

  //---------------------------
}
TimeSerie::~TimeSerie(){}

//Main function
void TimeSerie::plot_constant_in_time(){
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
