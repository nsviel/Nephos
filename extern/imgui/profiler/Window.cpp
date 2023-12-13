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
  this->prev_fps_frame_time = std::chrono::system_clock::now();
  this->fps_frames_count = 0;
  this->avg_frame_time = 1.0f;

  //---------------------------
}

//Main function
void Window::Render(){
  //---------------------------

  this->fps_counter();

  //Window stuff
  std::stringstream title;
  title.precision(2);
  title << std::fixed << "Profiler [" << avg_frame_time * 1000.0f << "ms" << "\t" << 1.0f / avg_frame_time << "fps" << "]###ProfilerWindow";
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

//Subfunction
void Window::fps_counter(){
  //---------------------------

  //Time stuff
  fps_frames_count++;
  auto currFrameTime = std::chrono::system_clock::now();{
    float fpsDeltaTime = std::chrono::duration<float>(currFrameTime - prev_fps_frame_time).count();
    if (fpsDeltaTime > 0.5f){
      this->avg_frame_time = fpsDeltaTime / float(fps_frames_count);
      fps_frames_count = 0;
      prev_fps_frame_time = currFrameTime;
    }
  }

  //---------------------------
}
void Window::truc(ImProfil::Graph graph){
  //---------------------------


  //---------------------------
}

}
