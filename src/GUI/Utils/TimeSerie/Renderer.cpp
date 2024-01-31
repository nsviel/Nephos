#include "Renderer.h"

#include <GUI/Utils/TimeSerie/Namespace.h>


namespace utl::gui::serie{

Renderer::Renderer(){
  //---------------------------

  this->graph = new utl::gui::serie::Graph();

  //---------------------------
}

//Main function
void Renderer::render_window(ImVec2 size){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 1));


  ImGui::BeginChild("##cpuProfiler", ImVec2(0, size.y));
  graph->render_timings(size);
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

  graph->render_timings(available_size);

  ImGui::End();

  //---------------------------
}


}
