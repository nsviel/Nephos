#include "Manager.h"

#include <Profiler/Namespace.h>


namespace prf::improfil{

Manager::Manager(){
  //---------------------------

  this->graph = new prf::improfil::Graph();
  this->idx_color = 0;
  this->max_nb_data = 100;
  this->vec_color = prf::improfil::colormap::viridis;

  //---------------------------
}
Manager::Manager(string name){
  //---------------------------

  this->name = name;
  this->graph = new prf::improfil::Graph();
  this->idx_color = 0;
  this->max_nb_data = 100;
  this->vec_color = prf::improfil::colormap::viridis;

  //---------------------------
}
Manager::~Manager(){}

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
  string title = name + "##graph";
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 1));
  ImGui::BeginChild(title.c_str(), ImVec2(0, dimension.y));
  graph->render_graph(dimension);
  ImGui::End();
  ImGui::PopStyleColor();
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + dimension.y + 5);

  //---------------------------
}
void Manager::load_data_to_graph(){
  //---------------------------

  this->graph->load_graph_data(vec_task);

  //---------------------------
}
void Manager::add_task(float ts_begin, float ts_end, string name){
  //---------------------------

  //Insert task
  prf::graph::structure::Task task;
  task.ts_begin = ts_begin;
  task.ts_end = ts_end;
  task.name = name;
  task.color = get_next_color();
  vec_task.push_back(task);

  //Remove old one
  if(vec_task.size() > max_nb_data) vec_task.erase(vec_task.begin());

  //---------------------------
}
void Manager::add_task(float ts_begin, float ts_end, string name, vec4 color){
  //---------------------------

  //Insert task
  prf::graph::structure::Task task;
  task.ts_begin = ts_begin;
  task.ts_end = ts_end;
  task.name = name;
  task.color = color;
  vec_task.push_back(task);

  //Remove old one
  if(vec_task.size() > max_nb_data) vec_task.erase(vec_task.begin());

  //---------------------------
}
void Manager::add_vec_task(vector<prf::graph::structure::Task> vec_task){
  //---------------------------

  this->vec_task = vec_task;

  for(int i=0; i<vec_task.size(); i++){
    prf::graph::structure::Task& task = vec_task[i];
    task.color = get_next_color();
  }

  //---------------------------
}
void Manager::reset(){
  //---------------------------

  this->vec_task.clear();
  this->idx_color = 0;

  //---------------------------
}

//Subfunction
vec4 Manager::get_next_color(){
  vec4 color;
  //---------------------------

  color = vec_color[idx_color];
  idx_color++;

  if(idx_color >= vec_color.size()) idx_color = 0;

  //---------------------------
  return color;
}
void Manager::set_time_max(int value){
  //---------------------------

  float* time_max = graph->get_max_time();
  *time_max = float(value) / 1000;

  //---------------------------
}

}
