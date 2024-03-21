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
  style.PlotMinSize = ImVec2(10, 10);
  style.PlotPadding = ImVec2(0,0);
  style.LineWeight = 2;
  style.FillAlpha = 0.5f;
  style.PlotMinSize = ImVec2(10, 10);
  style.PlotPadding = ImVec2(10, 10);

  style.Colors[ImPlotCol_PlotBg] = ImVec4(0, 0, 0, 1);


  //---------------------------
}

}
