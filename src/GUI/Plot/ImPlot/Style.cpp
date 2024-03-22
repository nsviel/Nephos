#include "Style.h"


namespace utl::implot{

//Constructor / Destructor
Style::Style(){
  //---------------------------


  //---------------------------
}
Style::~Style(){}

//Main function
void Style::make_style(){
  //---------------------------

  ImPlotStyle& style = ImPlot::GetStyle();

  //Style
  style.PlotMinSize = ImVec2(10, 10);
  style.PlotPadding = ImVec2(0,0);
  style.LineWeight = 2;
  style.FillAlpha = 0.5f;
  style.PlotMinSize = ImVec2(10, 10);
  style.PlotPadding = ImVec2(10, 10);
  style.Marker = ImPlotMarker_Circle;
  style.MarkerSize = 2;
  style.MarkerWeight = 1;
  style.FillAlpha = 1;

  //Color
  style.Colors[ImPlotCol_PlotBg] = ImVec4(0, 0, 0, 1);
  style.Colors[ImPlotCol_PlotBorder] = ImVec4(0, 0, 0, 1);
  style.Colors[ImPlotCol_FrameBg] = ImVec4(0.1, 0.1, 0.1, 1);
  style.Colors[ImPlotCol_AxisBgHovered] = ImVec4(0.1, 0.1, 0.1, 1);
  style.Colors[ImPlotCol_AxisBgActive] = ImVec4(0.1, 0.1, 0.1, 1);
  style.Colors[ImPlotCol_AxisBg] = ImVec4(0.1, 0.1, 0.1, 1);
  style.Colors[ImPlotCol_PlotBorder] = ImVec4(0.1, 0.1, 0.1, 1);

  //---------------------------
}

}
