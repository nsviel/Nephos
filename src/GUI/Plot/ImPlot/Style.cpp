#include "Style.h"


namespace utl::implot{

//Constructor / Destructor
Style::Style(){
  //---------------------------


  //---------------------------
  this->make_style();
}
Style::~Style(){}

//Main function
void Style::make_style(){
  //---------------------------

  ImPlotStyle& style = ImPlot::GetStyle();
  style.PlotMinSize = ImVec2(10, 10);
  style.PlotPadding = ImVec2(0,0);
  style.LineWeight = 2;

  //---------------------------
}

}
