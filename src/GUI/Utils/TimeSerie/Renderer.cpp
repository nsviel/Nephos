#include "Renderer.h"

#include <GUI/Utils/TimeSerie/Namespace.h>


namespace utl::gui::serie{

Renderer::Renderer(){
  //---------------------------

  this->legend_width = 200;
  this->max_graph_height = 300;
  this->graph = new utl::gui::serie::Graph();

  //---------------------------
}

//Main function
void Renderer::render_window(ImVec2 size){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 1));

  int margin_size = int(ImGui::GetStyle().ItemSpacing.y);
  int graph_height_available = (int(size.y) - margin_size);
  int graph_height = std::min(max_graph_height, graph_height_available);
  int graph_width = int(size.x) - legend_width;

  ImGui::BeginChild("##cpuProfiler", ImVec2(0, size.y));
  graph->render_timings(graph_width, legend_width, graph_height_available);
  ImGui::End();
/*
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + available_size.y + 5);

  ImGui::BeginChild("##gpuProfiler", ImVec2(0, available_size.y));
  graph_gpu->render_timings(graph_width, legend_width, graph_height_available, frame_offset);
  ImGui::End();
*/
  ImGui::PopStyleColor();

  //---------------------------
}
void Renderer::render_overlay(ImVec2 image_pose){
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

  graph->render_timings(graph_width, legend_width, graph_height_available);

  ImGui::End();

  //---------------------------
}


}
