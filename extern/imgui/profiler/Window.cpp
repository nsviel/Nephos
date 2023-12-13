#include "Window.h"


namespace ImProfil{

Window::Window(): cpuGraph(300), gpuGraph(300){
  //---------------------------

  stopProfiling = false;
  frameOffset = 0;
  frame_width = 3;
  frame_spacing = 1;
  use_colored_legend_text = true;
  prevFpsFrameTime = std::chrono::system_clock::now();
  fpsFramesCount = 0;
  avgFrameTime = 1.0f;

  //---------------------------
}

void Window::Render(){
  //---------------------------

  //Time stuff
  fpsFramesCount++;
  auto currFrameTime = std::chrono::system_clock::now();
  {
    float fpsDeltaTime = std::chrono::duration<float>(currFrameTime - prevFpsFrameTime).count();
    if (fpsDeltaTime > 0.5f)
    {
      this->avgFrameTime = fpsDeltaTime / float(fpsFramesCount);
      fpsFramesCount = 0;
      prevFpsFrameTime = currFrameTime;
    }
  }

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
  gpuGraph.RenderTimings(graphWidth, legendWidth, graphHeight, frameOffset);
  cpuGraph.RenderTimings(graphWidth, legendWidth, graphHeight, frameOffset);
  if (graphHeight * 2 + sizeMargin + sizeMargin < canvasSize.y){
    ImGui::Columns(2);
    size_t textSize = 50;
    ImGui::Checkbox("Stop profiling", &stopProfiling);
    //ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - textSize);
    ImGui::Checkbox("Colored legend text", &use_colored_legend_text);
    ImGui::DragInt("Frame offset", &frameOffset, 1.0f, 0, 400);
    ImGui::NextColumn();

    ImGui::SliderInt("Frame width", &frame_width, 1, 4);
    ImGui::SliderInt("Frame spacing", &frame_spacing, 0, 2);
    ImGui::SliderFloat("Transparency", &ImGui::GetStyle().Colors[ImGuiCol_WindowBg].w, 0.0f, 1.0f);
    ImGui::Columns(1);
  }
  if (!stopProfiling)
    frameOffset = 0;
  gpuGraph.frame_width = frame_width;
  gpuGraph.frame_spacing = frame_spacing;
  gpuGraph.use_colored_legend_text = use_colored_legend_text;
  cpuGraph.frame_width = frame_width;
  cpuGraph.frame_spacing = frame_spacing;
  cpuGraph.use_colored_legend_text = use_colored_legend_text;

  ImGui::End();

  //---------------------------
}

}
