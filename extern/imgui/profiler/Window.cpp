#include "Window.h"


namespace ImProfil{

Window::Window(){
  //---------------------------

  this->cpu_graph = new ImProfil::Graph(300);
  this->gpu_graph = new ImProfil::Graph(300);

  this->stop_profiling = false;
  this->frame_offset = 0;
  this->frame_width = 3;
  this->frame_spacing = 1;
  this->use_colored_legend_text = true;
  this->prevFpsFrameTime = std::chrono::system_clock::now();
  this->fpsFramesCount = 0;
  this->avgFrameTime = 1.0f;

  //---------------------------
}

void Window::Render(){
  //---------------------------

  //Time stuff
  fpsFramesCount++;
  auto currFrameTime = std::chrono::system_clock::now();{
    float fpsDeltaTime = std::chrono::duration<float>(currFrameTime - prevFpsFrameTime).count();
    if (fpsDeltaTime > 0.5f){
      this->avgFrameTime = fpsDeltaTime / float(fpsFramesCount);
      fpsFramesCount = 0;
      prevFpsFrameTime = currFrameTime;
    }
  }

  //Window stuff
  std::stringstream title;
  title.precision(2);
  title << std::fixed << "Profiler [" << avgFrameTime * 1000.0f << "ms" << "\t" << 1.0f / avgFrameTime << "fps" << "]###ProfilerWindow";
  //###AnimatedTitle
  ImGui::Begin(title.str().c_str(), 0, ImGuiWindowFlags_NoScrollbar);

  ImVec2 canvasSize = ImGui::GetContentRegionAvail();
  int sizeMargin = int(ImGui::GetStyle().ItemSpacing.y);
  int maxGraphHeight = 300;
  int availableGraphHeight = (int(canvasSize.y) - sizeMargin) / 2;
  int graphHeight = std::min(maxGraphHeight, availableGraphHeight);
  int legendWidth = 200;
  int graphWidth = int(canvasSize.x) - legendWidth;
  gpu_graph->render_timings(graphWidth, legendWidth, graphHeight, frame_offset);
  cpu_graph->render_timings(graphWidth, legendWidth, graphHeight, frame_offset);
  if (graphHeight * 2 + sizeMargin + sizeMargin < canvasSize.y){
    ImGui::Columns(2);
    size_t textSize = 50;
    ImGui::Checkbox("Stop profiling", &stop_profiling);
    //ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - textSize);
    ImGui::Checkbox("Colored legend text", &use_colored_legend_text);
    ImGui::DragInt("Frame offset", &frame_offset, 1.0f, 0, 400);
    ImGui::NextColumn();

    ImGui::SliderInt("Frame width", &frame_width, 1, 4);
    ImGui::SliderInt("Frame spacing", &frame_spacing, 0, 2);
    ImGui::SliderFloat("Transparency", &ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w, 0.0f, 1.0f);
    ImGui::Columns(1);
  }
  if (!stop_profiling)
    frame_offset = 0;
  gpu_graph->frame_width = frame_width;
  gpu_graph->frame_spacing = frame_spacing;
  gpu_graph->use_colored_legend_text = use_colored_legend_text;
  cpu_graph->frame_width = frame_width;
  cpu_graph->frame_spacing = frame_spacing;
  cpu_graph->use_colored_legend_text = use_colored_legend_text;

  ImGui::End();

  //---------------------------
}
void Window::truc(ImProfil::Graph graph){
  //---------------------------



  //---------------------------
}

}
