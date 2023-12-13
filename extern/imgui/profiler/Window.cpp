#include "Window.h"


namespace ImProfil{

Window::Window(){
  //---------------------------

  this->stop_profiling = false;
  this->frame_offset = 0;
  this->frame_width = 1;
  this->frame_spacing = 1;
  this->use_colored_legend_text = true;
  this->prev_fps_frame_time = std::chrono::system_clock::now();
  this->fps_frames_count = 0;
  this->avg_frame_time = 1.0f;
  this->legend_width = 200;
  this->max_graph_height = 300;

  //---------------------------
  this->init_graph();
}

//Main function
void Window::Render_window(){
  //---------------------------

  this->fps_counter();

  //###AnimatedTitle
  std::stringstream title;
  title.precision(2);
  title << std::fixed << "Profiler [" << avg_frame_time * 1000.0f << "ms" << "\t" << 1.0f / avg_frame_time << "fps" << "]###ProfilerWindow";
  ImGui::Begin(title.str().c_str(), 0, ImGuiWindowFlags_NoScrollbar);

  ImVec2 available_size = ImGui::GetContentRegionAvail();
  int margin_size = int(ImGui::GetStyle().ItemSpacing.y);
  int graph_height_available = (int(available_size.y) - margin_size);
  int graph_height = std::min(max_graph_height, graph_height_available);
  int graph_width = int(available_size.x) - legend_width;

  graph->render_timings(graph_width, legend_width, graph_height_available, frame_offset);

  ImGui::End();

  //---------------------------
}
void Window::Render_overlay(ImVec2 image_pose){
  //---------------------------

  ImGui::SetNextWindowPos(image_pose, ImGuiCond_Always);
  ImGui::SetNextWindowBgAlpha(0.0f);
  ImGui::SetNextWindowSize(ImVec2(300, 75));
  ImGuiWindowFlags flags;
  flags |= ImGuiWindowFlags_NoMove;
  flags |= ImGuiWindowFlags_NoTitleBar;
  flags |= ImGuiWindowFlags_NoResize;
  flags |= ImGuiWindowFlags_NoSavedSettings;
  flags |= ImGuiWindowFlags_NoFocusOnAppearing;
  flags |= ImGuiWindowFlags_NoNav;
  flags |= ImGuiWindowFlags_NoNavFocus;
  flags |= ImGuiWindowFlags_NoScrollbar;

  ImGui::Begin("##profiler_overlay", 0, flags);

  ImVec2 available_size = ImGui::GetContentRegionAvail();
  int margin_size = int(ImGui::GetStyle().ItemSpacing.y);
  int graph_height_available = (int(available_size.y) - margin_size);
  int graph_height = std::min(max_graph_height, graph_height_available);
  int graph_width = int(available_size.x) - legend_width;

  graph->render_timings(graph_width, legend_width, graph_height_available, frame_offset);

  ImGui::End();

  //---------------------------
}

//Subfunction
void Window::init_graph(){
  //---------------------------

  this->graph = new ImProfil::Graph(300);
  graph->frame_width = frame_width;
  graph->frame_spacing = frame_spacing;
  graph->use_colored_legend_text = use_colored_legend_text;

  //---------------------------
}
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
void Window::display_option(){
  //---------------------------

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

  if (!stop_profiling)
    frame_offset = 0;

  //---------------------------
}

}
