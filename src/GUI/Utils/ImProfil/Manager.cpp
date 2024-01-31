#include "Manager.h"

#include <GUI/Utils/ImProfil/Namespace.h>


namespace utl::improfil{

Manager::Manager(){
  //---------------------------

  this->graph = new utl::improfil::Graph();
  this->idx_color = 0;
  this->max_nb_data = 100;

  //---------------------------
  this->init_color();
}

//Main function
void Manager::render_overlay(ImVec2 image_pose){
  //---------------------------
/*
  renderer.graph->load_graph_data(vec_task);

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

  graph->render_graph(available_size);

  ImGui::End();
*/
  //---------------------------
}
void Manager::render_child(ImVec2 dimension){
  //---------------------------

  this->graph->load_graph_data(vec_task);

  ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 1));
  ImGui::BeginChild("##cpuProfiler", ImVec2(0, dimension.y));
  graph->render_graph(dimension);
  ImGui::End();
  ImGui::PopStyleColor();

  /*
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + size.y + 5);

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 1));
    ImGui::BeginChild("##gpuProfiler", ImVec2(0, size.y));
    graph_1->render_graph(size);
    ImGui::End();
    ImGui::PopStyleColor();
  */

  //---------------------------
}
void Manager::add_task(float time_beg, float time_end, string name){
  //---------------------------

  utl::improfil::Task task;
  vec4 color = get_next_color();
  task = {time_beg, time_end, name, color};
  vec_task.push_back(task);
  if(vec_task.size() > max_nb_data) vec_task.erase(vec_task.begin());

  //---------------------------
}
void Manager::reset(){
  //---------------------------

  this->vec_task.clear();
  this->idx_color = 0;

  //---------------------------
}

//Subfunction
void Manager::init_color(){
  //---------------------------

  //Profiler bar colors in order of appearance
  vec_color.clear();
  vec_color.push_back(utl::improfil::color::viridis_3);
  vec_color.push_back(utl::improfil::color::viridis_4);
  vec_color.push_back(utl::improfil::color::viridis_5);
  vec_color.push_back(utl::improfil::color::viridis_6);
  vec_color.push_back(utl::improfil::color::viridis_7);
  vec_color.push_back(utl::improfil::color::viridis_8);
  vec_color.push_back(utl::improfil::color::viridis_9);

  //---------------------------
}
vec4 Manager::get_next_color(){
  vec4 color;
  //---------------------------

  color = vec_color[idx_color];
  idx_color++;

  if(idx_color >= vec_color.size()) idx_color = 0;

  //---------------------------
  return color;
}

}
