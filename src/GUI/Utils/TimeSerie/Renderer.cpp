#include "Renderer.h"

#include <GUI/Utils/TimeSerie/Namespace.h>


namespace utl::gui::serie{

Renderer::Renderer(){
  //---------------------------

  this->graph_0 = new utl::gui::serie::Graph();
  this->graph_1 = new utl::gui::serie::Graph();

  //---------------------------
}

//Main function
void Renderer::render_window(ImVec2 size){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 1));


  ImGui::BeginChild("##cpuProfiler", ImVec2(0, size.y));
  graph_0->render_timings(size);
  ImGui::End();

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + size.y + 5);

  ImGui::BeginChild("##gpuProfiler", ImVec2(0, size.y));
  graph_1->render_timings(size);
  ImGui::End();

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

  graph_0->render_timings(available_size);

  ImGui::End();

  //---------------------------
}


}
