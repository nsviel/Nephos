#include "Style.h"

#include <Utility/Element/Color/Namespace.h>
#include <Utility/Function/Type/Casting.h>


namespace utl::implot{

//Constructor / Destructor
Style::Style(){
  //---------------------------



  //---------------------------
}
Style::~Style(){}

//Main function
void Style::make_style(){
  if(applied) return;
  //---------------------------

  this->make_style_parameter();
  this->make_custom_colormap();

  //---------------------------
  this->applied = true;
}

//Subfunction
void Style::make_style_parameter(){
  //---------------------------

  ImPlotStyle& style = ImPlot::GetStyle();

  //Style
  style.PlotMinSize = ImVec2(10, 10);
  style.PlotPadding = ImVec2(0, 0);
  style.LineWeight = 1;
  style.PlotMinSize = ImVec2(10, 10);
  style.PlotPadding = ImVec2(10, 10);
  style.Marker = ImPlotMarker_Circle;
  style.MarkerSize = 2;
  style.MarkerWeight = 1;
  style.FillAlpha = 1.0f;
  //style.Colormap = ImPlotColormap_Viridis;

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
void Style::make_custom_colormap(){
  //---------------------------

  if(heatmap == -1){
    std::vector<ImU32> data = type::vec_vec3_to_ImU32(utl::colormap::viridis_long);

    heatmap = ImPlot::AddColormap("Heatmap", data.data(), data.size());
  }

  //---------------------------
}

}
