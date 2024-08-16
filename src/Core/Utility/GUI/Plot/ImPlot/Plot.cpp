#include "Plot.h"
#include "Namespace.h"

#include <imgui/implot/implot.h>
#include <algorithm>


namespace utl::implot{

Plot::Plot(){
  //---------------------------

  this->implot_style = new utl::implot::Style();

  //---------------------------
}
Plot::~Plot(){}

//Main function
void Plot::plot_heatmap(utl::base::Plot* plot){
  //---------------------------

  // Push the custom colormap onto the colormap stack
  ImPlot::PushColormap(implot_style->get_colormap_heatmap());

  ImPlot::ColormapScale("##HeatScale", plot->axis_z.min, plot->axis_z.max, ImVec2(60, plot->dimension[1]));
  ImGui::SameLine();

  // Begin a new plot
  ImPlotFlags flag;
  flag |= ImPlotFlags_NoBoxSelect;
  flag |= ImPlotFlags_NoMouseText;
  flag |= ImPlotFlags_NoLegend;
  flag |= ImPlotFlags_CanvasOnly;
  if(ImPlot::BeginPlot(plot->title.c_str(), ImVec2(-1, plot->dimension[1]), flag)){
    ImPlotAxisFlags axis_flag;
    axis_flag |= ImPlotAxisFlags_AutoFit;
    axis_flag |= ImPlotAxisFlags_Foreground;
    ImPlot::SetupAxes(nullptr, nullptr, axis_flag, axis_flag);

    // Plot the heatmap
    std::string truc = plot->title + "##heatmap";
    ImPlot::PlotHeatmap(truc.c_str(), plot->axis_z.data.data(), plot->axis_x.size, plot->axis_y.size, plot->axis_z.min, plot->axis_z.max, nullptr, ImPlotPoint(plot->axis_x.min, plot->axis_y.min), ImPlotPoint(plot->axis_x.max, plot->axis_y.max));

    // End the plot
    ImPlot::EndPlot();
  }

  ImPlot::PopColormap();

  //---------------------------
}
bool Plot::plot_heatmap(utl::base::Plot* plot, utl::base::Axis* x_axis, utl::base::Axis* y_axis){
  bool dragged = false;
  //---------------------------

  // Push the custom colormap onto the colormap stack
  ImPlot::PushColormap(implot_style->get_colormap_heatmap());

  ImPlot::ColormapScale("##HeatScale",plot->axis_z.min, plot->axis_z.max, ImVec2(60, plot->dimension[1]));
  ImGui::SameLine();

  // Begin a new plot
  ImPlotFlags flag;
  flag |= ImPlotFlags_NoBoxSelect;
  flag |= ImPlotFlags_NoMouseText;
  flag |= ImPlotFlags_NoLegend;
  flag |= ImPlotFlags_CanvasOnly;
  ImPlot::SetNextAxisLimits(ImAxis_X1, 0, 10);
  ImPlot::SetNextAxisLimits(ImAxis_Y1, 0, 90);
  if(ImPlot::BeginPlot(plot->title.c_str(), ImVec2(-1, plot->dimension[1]), flag)){
    //Axis configuration
    ImPlotAxisFlags axis_x_flag;
    axis_x_flag |= ImPlotAxisFlags_LockMin;
    axis_x_flag |= ImPlotAxisFlags_AutoFit;
    axis_x_flag |= ImPlotAxisFlags_Foreground;
    ImPlotAxisFlags axis_y_flag;
    axis_y_flag |= ImPlotAxisFlags_Foreground;
    axis_y_flag |= ImPlotAxisFlags_LockMin;
    axis_y_flag |= ImPlotAxisFlags_LockMax;
    ImPlot::SetupAxes(nullptr, nullptr, axis_x_flag, axis_y_flag);

    // Plot the heatmap
    std::string ID = plot->title + "##heatmap";
    ImPlot::PlotHeatmap(ID.c_str(), plot->axis_z.data.data(), plot->axis_y.size, plot->axis_x.size, plot->axis_z.min, plot->axis_z.max, nullptr, ImPlotPoint(plot->axis_x.min, plot->axis_y.min), ImPlotPoint(plot->axis_x.max, plot->axis_y.max));

    // Draw x bounds
    float y_height[2] = {y_axis->bound[0], y_axis->bound[1]};
    float x_bound_min[2] = {x_axis->bound[0], x_axis->bound[0]};
    ImPlot::SetNextLineStyle(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), 2.0f);
    ImPlot::PlotLine("X bound min", x_bound_min, y_height, 2);
    float x_bound_max[2] = {x_axis->bound[1], x_axis->bound[1]};
    ImPlot::SetNextLineStyle(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), 2.0f);
    ImPlot::PlotLine("X bound max", x_bound_max, y_height, 2);

    // Draw y bounds
    float x_width[2] = {x_axis->bound[0], x_axis->bound[1]};
    float y_bound_min[2] = {y_axis->bound[0], y_axis->bound[0]};
    ImPlot::SetNextLineStyle(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), 2.0f);
    ImPlot::PlotLine("Y bound min", x_width, y_bound_min, 2);
    float y_bound_max[2] = {y_axis->bound[1], y_axis->bound[1]};
    ImPlot::SetNextLineStyle(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), 2.0f);
    ImPlot::PlotLine("Y bound max", x_width, y_bound_max, 2);

    //Dragging line
    if(ImPlot::IsPlotHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)){
      if(x_axis->current < x_axis->bound[0]) x_axis->current = x_axis->bound[0];
      if(x_axis->current > x_axis->bound[1]) x_axis->current = x_axis->bound[1];
      ImPlotPoint mouse = ImPlot::GetPlotMousePos();

      //X current
      if(mouse.x > x_axis->bound[0] && mouse.x < x_axis->bound[1]){
        x_axis->current = mouse.x;
        dragged = true;
      }

      //Y current
      if(mouse.y > y_axis->bound[0] && mouse.y < y_axis->bound[1]){
        y_axis->current = mouse.y;
        dragged = true;
      }
    }
    float x_current[2] = {x_axis->current, x_axis->current};
    ImPlot::SetNextLineStyle(ImVec4(1.0f, 0.1f, 0.1f, 0.8f), 1.0f);
    ImPlot::PlotLine("X current", x_current, y_height, 2);
    float y_current[2] = {y_axis->current, y_axis->current};
    ImPlot::SetNextLineStyle(ImVec4(0.1f, 1.0f, 0.1f, 0.8f), 1.0f);
    ImPlot::PlotLine("Y current", x_width, y_current, 2);

    //Line floating text
    ImPlot::PlotText(std::to_string(x_axis->current).c_str(), x_axis->current, plot->axis_y.max, ImVec2(10, 50), ImPlotTextFlags_Vertical);
    ImPlot::PlotText(std::to_string(y_axis->current).c_str(), plot->axis_x.max, y_axis->current, ImVec2(-20, -10));

    // End the plot
    ImPlot::EndPlot();
  }

  ImPlot::PopColormap();

  //---------------------------
  return dragged;
}
void Plot::plot_regression(utl::base::Plot* plot){
  implot_style->make_style();
  //---------------------------

  // Create a window
  ImPlotFlags flag;
  flag |= ImPlotFlags_NoBoxSelect;
  flag |= ImPlotFlags_NoMouseText;
  flag |= ImPlotFlags_NoLegend;
  flag |= ImPlotFlags_CanvasOnly;
  if(ImPlot::BeginPlot(plot->title.c_str(), ImVec2(-1, plot->dimension[1]), flag)){
    ImPlotAxisFlags axis_flag;
    axis_flag |= ImPlotAxisFlags_AutoFit;
    axis_flag |= ImPlotAxisFlags_Foreground;
    ImPlot::SetupAxes(plot->axis_x_name.c_str(), plot->axis_x_name.c_str(), axis_flag, axis_flag);

    // Plot the data
    std::string ID = plot->title + "##scatter";
    ImPlot::PlotScatter(ID.c_str(), plot->axis_x.data.data(), plot->axis_y.data.data(), plot->axis_x.data.size());

    // Plot an additional point in a different color
    if(plot->highlight != glm::vec2(-1, -1)){
      ImVec4 color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
      ImPlot::PushStyleColor(ImPlotCol_MarkerFill, color);
      ImPlot::PushStyleColor(ImPlotCol_MarkerOutline, color);
      std::string machin = plot->title + "##highlight";
      ImPlot::PlotScatter(machin.c_str(), &plot->highlight.x, &plot->highlight.y, 1);
      ImPlot::PopStyleColor(2);
    }

    // Plot the regression line
    if(plot->axis_y.fitting.size() != 0){
      std::string ID = plot->title + "##fitting";
      ImPlot::PushStyleColor(ImPlotCol_Line, IM_COL32(255, 0, 0, 255));
      ImPlot::PushStyleVar(ImPlotStyleVar_MarkerSize, 1);
      ImPlot::PlotScatter(ID.c_str(), plot->axis_x.data.data(), plot->axis_y.fitting.data(), plot->axis_y.fitting.size());
      ImPlot::PopStyleVar();
      ImPlot::PopStyleColor();
    }

    // End the plot
    ImPlot::EndPlot();
  }

  //---------------------------
}
void Plot::plot_scatter(utl::base::Plot* plot){
  //---------------------------

  // Create a window
  ImPlotFlags flag;
  flag |= ImPlotFlags_NoBoxSelect;
  flag |= ImPlotFlags_NoMouseText;
  flag |= ImPlotFlags_NoLegend;
  flag |= ImPlotFlags_CanvasOnly;
  if(ImPlot::BeginPlot(plot->title.c_str(), ImVec2(-1, plot->dimension[1]), flag)){
    ImPlotAxisFlags axis_flag;
    axis_flag |= ImPlotAxisFlags_AutoFit;
    axis_flag |= ImPlotAxisFlags_Foreground;
    ImPlot::SetupAxes(plot->axis_x_name.c_str(), plot->axis_x_name.c_str(), axis_flag, axis_flag);

    // Plot the data
    std::string truc = plot->title + "##scatter";
    ImPlot::PlotScatter(truc.c_str(), plot->axis_x.data.data(), plot->axis_y.data.data(), plot->axis_x.data.size());

    // Plot an additional point in a different color
    if(plot->highlight != glm::vec2(-1, -1)){
      ImVec4 color = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
      ImPlot::PushStyleColor(ImPlotCol_MarkerFill, color);
      ImPlot::PushStyleColor(ImPlotCol_MarkerOutline, color);
      std::string machin = plot->title + "##highlight";
      ImPlot::PlotScatter(machin.c_str(), &plot->highlight.x, &plot->highlight.y, 1);
      ImPlot::PopStyleColor(2);
    }

    // End the plot
    ImPlot::EndPlot();
  }

  //---------------------------
}
void Plot::plot_scatter_rdm(){
  //---------------------------

  // Generate random data
  static std::vector<double> x_data, y_data;
  const int num_points = 100;
  if(x_data.size() == 0){
    for(int i = 0; i < num_points; ++i){
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

  static std::vector<float> vec_c;
  static std::vector<float> vec_d;
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

    std::string value = std::to_string(vec_d[0]) + " fps";
    ImPlot::PlotText(value.c_str(), cpt - 10, vec_d[0] + 5);
    ImPlot::PlotLine("", vec_c.data(), vec_d.data(), vec_d.size());
    ImPlot::PlotShaded("", vec_c.data(), vec_d.data(), vec_d.size(), -INFINITY, 0);

    ImPlot::PopStyleColor();

    ImPlot::EndPlot();
  }

  //---------------------------
}
void Plot::plot_temperature(float temp_cpu, float temp_gpu){
  implot_style->make_style();
  int nb_element = 300;
  //---------------------------

  static std::vector<float> vec_time;
  static std::vector<float> cpu_temps;
  static std::vector<float> gpu_temps;
  static int cpt = 0;
  static float max_gpu = 0;
  static float max_cpu = 0;

  cpt++;

  cpu_temps.push_back(temp_cpu);
  gpu_temps.push_back(temp_gpu);
  vec_time.push_back(cpt);

  if(cpu_temps.size() > nb_element) cpu_temps.erase(cpu_temps.begin());
  if(gpu_temps.size() > nb_element) gpu_temps.erase(gpu_temps.begin());
  if(vec_time.size() > nb_element) vec_time.erase(vec_time.begin());

  float max_current_cpu = (float)*std::max_element(cpu_temps.begin(), cpu_temps.end());
  float max_current_gpu = (float)*std::max_element(gpu_temps.begin(), gpu_temps.end());
  if(max_current_cpu > max_cpu) max_cpu = max_current_cpu;
  if(max_current_gpu > max_gpu) max_gpu = max_current_gpu;

  //Plot
  ImPlotFlags flag;
  flag |= ImPlotFlags_NoBoxSelect;
  flag |= ImPlotFlags_NoMouseText;
  flag |= ImPlotFlags_NoLegend;
  flag |= ImPlotFlags_CanvasOnly;
  if(ImPlot::BeginPlot("##Temperature", ImVec2(-1, -1), flag)){
    ImPlot::SetupAxisLimitsConstraints(ImAxis_Y1, 0, 100);
    ImPlot::SetupAxisZoomConstraints(ImAxis_Y1, 0, 100);
    ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_NoDecorations, 0);
    ImPlot::SetupAxisLimits(ImAxis_X1, cpt - nb_element, cpt, ImGuiCond_Always);
    ImPlot::SetupAxisLimits(ImAxis_Y1, 0, 100);
    ImPlot::PushStyleVar(ImPlotStyleVar_LineWeight, 1.0f);
    ImPlot::PushStyleVar(ImPlotStyleVar_MarkerSize, 1.0f);

    // Plot GPU temperature
    ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
    ImPlot::PlotLine("GPU Temp", vec_time.data(), gpu_temps.data(), gpu_temps.size());
    ImPlot::PushStyleColor(ImPlotCol_Fill, ImVec4(0.3f, 0.5f, 0.3f, 0.5f));
    ImPlot::PlotShaded("GPU Temp", vec_time.data(), gpu_temps.data(), gpu_temps.size(), -INFINITY, 0);
    ImPlot::PopStyleColor(2);
    ImPlot::PushStyleColor(ImPlotCol_Line, ImVec4(0.2f, 0.6f, 0.2f, 1.0f));
    std::vector<float> gpu_max(vec_time.size(), max_current_gpu);
    ImPlot::PlotLine("GPU Line", vec_time.data(), gpu_max.data(), gpu_max.size());
    ImPlot::PopStyleColor();

    // Plot CPU temperature
    ImPlot::PlotLine("CPU Temp", vec_time.data(), cpu_temps.data(), cpu_temps.size());
    ImPlot::PlotShaded("CPU Temp", vec_time.data(), cpu_temps.data(), cpu_temps.size(), -INFINITY, 0);
    std::vector<float> cpu_max(vec_time.size(), max_current_cpu);
    ImPlot::PlotLine("CPU Line", vec_time.data(), cpu_max.data(), cpu_max.size());

    //Line floating text
    ImPlot::PlotText(std::to_string(temp_cpu).c_str(), cpt, max_current_cpu, ImVec2(-100, 50));
    ImPlot::PlotText(std::to_string(temp_gpu).c_str(), cpt, max_current_gpu, ImVec2(-100, 50));

    ImPlot::PopStyleVar(2);
    ImPlot::EndPlot();
  }

  //---------------------------
}

}
