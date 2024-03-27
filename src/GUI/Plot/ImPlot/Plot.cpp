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
void Plot::plot_heatmap(utl::type::Plot* utl_plot){
  implot_style->make_style();
  //---------------------------

  // Push the custom colormap onto the colormap stack
  ImPlot::PushColormap(implot_style->get_colormap_heatmap());

  static float scale_min = 1;
  static float scale_max = 20000;
  ImGui::DragFloatRange2("Scale",&scale_min, &scale_max, 100, 0, 60000);
  ImPlot::ColormapScale("##HeatScale",scale_min, scale_max, ImVec2(60,225));
  ImGui::SameLine();

  // Begin a new plot
  ImPlotFlags flag;
  flag |= ImPlotFlags_NoBoxSelect;
  flag |= ImPlotFlags_NoMouseText;
  flag |= ImPlotFlags_NoLegend;
  flag |= ImPlotFlags_CanvasOnly;
  if(ImPlot::BeginPlot(utl_plot->title.c_str(), ImVec2(-1, utl_plot->dimension.y), flag)){
    ImPlotAxisFlags axis_flag;
    axis_flag |= ImPlotAxisFlags_AutoFit;
    axis_flag |= ImPlotAxisFlags_Foreground;
    ImPlot::SetupAxes(nullptr, nullptr, axis_flag, axis_flag);

    // Plot the heatmap
    string truc = utl_plot->title + "##heatmap";
    ImPlot::PlotHeatmap(truc.c_str(), utl_plot->vec_z.data(), utl_plot->y_size, utl_plot->x_size, scale_min, scale_max, nullptr, ImPlotPoint(utl_plot->x_min, utl_plot->y_min), ImPlotPoint(utl_plot->x_max, utl_plot->y_max));

    // End the plot
    ImPlot::EndPlot();
  }

  ImPlot::PopColormap();

  //---------------------------
}
void Plot::plot_scatter(utl::type::Plot* utl_plot){
  implot_style->make_style();
  //---------------------------

  // Create a window
  ImPlotFlags flag;
  flag |= ImPlotFlags_NoBoxSelect;
  flag |= ImPlotFlags_NoMouseText;
  flag |= ImPlotFlags_NoLegend;
  flag |= ImPlotFlags_CanvasOnly;
  if(ImPlot::BeginPlot(utl_plot->title.c_str(), ImVec2(-1, utl_plot->dimension.y), flag)){
    ImPlotAxisFlags axis_flag;
    axis_flag |= ImPlotAxisFlags_AutoFit;
    axis_flag |= ImPlotAxisFlags_Foreground;
    ImPlot::SetupAxes(utl_plot->x_axis_name.c_str(), utl_plot->x_axis_name.c_str(), axis_flag, axis_flag);

    // Plot the data
    string truc = utl_plot->title + "##scatter";
    ImPlot::PlotScatter(truc.c_str(), utl_plot->vec_x.data(), utl_plot->vec_y.data(), utl_plot->vec_x.size());

    // Plot an additional point in a different color
    if(utl_plot->highlight != vec2(-1, -1)){
      ImVec4 color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
      ImPlot::PushStyleColor(ImPlotCol_MarkerFill, color);
      ImPlot::PushStyleColor(ImPlotCol_MarkerOutline, color);
      string machin = utl_plot->title + "##highlight";
      ImPlot::PlotScatter(machin.c_str(), &utl_plot->highlight.x, &utl_plot->highlight.y, 1);
      ImPlot::PopStyleColor(2);
    }

    // End the plot
    ImPlot::EndPlot();
  }

  //---------------------------
}
void Plot::plot_scatter_rdm(){
  implot_style->make_style();
  //---------------------------

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
  ImPlotFlags flag;
  flag |= ImPlotFlags_NoBoxSelect;
  flag |= ImPlotAxisFlags_AutoFit;
  flag |= ImPlotFlags_NoMouseText;
  flag |= ImPlotFlags_NoLegend;
  if(ImPlot::BeginPlot("##scatter_plot", ImVec2(-1, -1), flag)){
    ImPlotAxisFlags axis_flag;
    axis_flag |= ImPlotAxisFlags_AutoFit;
    ImPlot::SetupAxes(nullptr, nullptr, axis_flag, axis_flag);

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



    ImPlot::SetupAxisLimitsConstraints(ImAxis_Y1, 0, 60);
    ImPlot::SetupAxisZoomConstraints(ImAxis_Y1, 0, 60);
    ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_NoDecorations, 0);
    ImPlot::SetupAxisLimits(ImAxis_X1, cpt - 100, cpt, ImGuiCond_Always);
    ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 60);

    string value = to_string(vec_d[0]) + " fps";
    ImPlot::PlotText(value.c_str(), cpt - 10, vec_d[0] + 5);
    ImPlot::PlotLine("", vec_c.data(), vec_d.data(), vec_d.size());
    ImPlot::PlotShaded("", vec_c.data(), vec_d.data(), vec_d.size(), -INFINITY, 0);

    ImPlot::PopStyleColor();

    ImPlot::EndPlot();
  }

  //---------------------------
}

}
