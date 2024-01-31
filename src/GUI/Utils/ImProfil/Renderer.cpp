#include "Renderer.h"

#include <GUI/Utils/ImProfil/Namespace.h>


namespace utl::gui::serie{

Renderer::Renderer(){
  //---------------------------

  this->graph_0 = new utl::gui::serie::Graph();
  this->graph_1 = new utl::gui::serie::Graph();
  this->idx_color = 0;
  this->max_nb_data = 100;

  //---------------------------
  this->init_color();
}

//Main function
void Renderer::loop_overlay(ImVec2 image_pose){
  //---------------------------
/*
  renderer.graph_0->load_graph_data(vec_task);
  renderer.render_overlay(image_pose);
*/
  //---------------------------
}
void Renderer::loop_window(){
  //---------------------------
/*
  renderer.graph_0->load_graph_data(vec_task);
  renderer.graph_1->load_graph_data(vec_task);
  ImVec2 available_size = ImGui::GetContentRegionAvail();
  available_size.y = available_size.y / 2 - 2.5;
  renderer.render_child(available_size);
*/
  //---------------------------
}
void Renderer::add_task(float time_beg, float time_end, string name){
  //---------------------------
/*
  utl::gui::serie::Task task;
  vec4 color = renderer.get_next_color();
  task = {time_beg, time_end, name, color};
  vec_task.push_back(task);
  if(vec_task.size() > max_nb_data) vec_task.erase(vec_task.begin());
*/
  //---------------------------
}
void Renderer::render_child(ImVec2 size){
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 1));
  ImGui::BeginChild("##cpuProfiler", ImVec2(0, size.y));
  graph_0->render_graph(size);
  ImGui::End();
  ImGui::PopStyleColor();

  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + size.y + 5);

  ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 1));
  ImGui::BeginChild("##gpuProfiler", ImVec2(0, size.y));
  graph_1->render_graph(size);
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

  graph_0->render_graph(available_size);

  ImGui::End();

  //---------------------------
}
void Renderer::reset(){
  //---------------------------

  this->vec_task.clear();
  this->idx_color = 0;

  //---------------------------
}

//Subfunction
void Renderer::init_color(){
  //---------------------------

  //Profiler bar colors in order of appearance
  vec_color.clear();
  vec_color.push_back(utl::gui::serie::color::viridis_3);
  vec_color.push_back(utl::gui::serie::color::viridis_4);
  vec_color.push_back(utl::gui::serie::color::viridis_5);
  vec_color.push_back(utl::gui::serie::color::viridis_6);
  vec_color.push_back(utl::gui::serie::color::viridis_7);
  vec_color.push_back(utl::gui::serie::color::viridis_8);
  vec_color.push_back(utl::gui::serie::color::viridis_9);

  //---------------------------
}
vec4 Renderer::get_next_color(){
  vec4 color;
  //---------------------------

  color = vec_color[idx_color];
  idx_color++;

  if(idx_color >= vec_color.size()) idx_color = 0;

  //---------------------------
  return color;
}

}
