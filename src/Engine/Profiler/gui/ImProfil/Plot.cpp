#include "Plot.h"

#include <Profiler/Namespace.h>


namespace prf::improfil{

Plot::Plot(){
  //---------------------------

  this->renderer = new prf::improfil::Renderer();
  this->idx_color = 0;
  this->max_nb_data = 100;
  this->vec_color = prf::improfil::colormap::viridis;

  //---------------------------
}
Plot::Plot(string name){
  //---------------------------

  this->name = name;
  this->renderer = new prf::improfil::Renderer();
  this->idx_color = 0;
  this->max_nb_data = 100;
  this->vec_color = prf::improfil::colormap::viridis;

  //---------------------------
}
Plot::~Plot(){}

//Main function
void Plot::render(std::string name, ImVec2 dimension){
  string title = name + "##renderer";
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 1));
  ImGui::BeginChild(title.c_str(), ImVec2(0, dimension.y));
  renderer->render_graph(dimension);
  ImGui::End();
  ImGui::PopStyleColor();
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + dimension.y + 5);

  //---------------------------
}
void Plot::update(){
  //---------------------------

  renderer->load_graph_data(vec_task);

  //---------------------------
}
void Plot::reset(){
  //---------------------------

  this->vec_task.clear();
  this->idx_color = 0;

  //---------------------------
}

//Task function
void Plot::add_task(float ts_begin, float ts_end, string name, glm::vec4 color){
  //---------------------------

  //Insert task
  prf::graph::structure::Task task;
  task.ts_begin = ts_begin;
  task.ts_end = ts_end;
  task.name = name;
  task.color = (color == glm::vec4(0, 0, 0, 0)) ? get_next_color() : color;
  vec_task.push_back(task);

  //Remove old one
  if(vec_task.size() > max_nb_data) vec_task.erase(vec_task.begin());

  //---------------------------
}
void Plot::add_vec_task(vector<prf::graph::structure::Task> vec_task){
  //---------------------------

  //Assign tasks
  for(int i=0; i<vec_task.size(); i++){
    prf::graph::structure::Task& task = vec_task[i];

    if(task.color == vec4(0, 0, 0, 0)){
      this->add_task(task.ts_begin, task.ts_end, task.name);
    }else{
      this->add_task(task.ts_begin, task.ts_end, task.name, task.color);
    }
  }

  //---------------------------
}

//Subfunction
vec4 Plot::get_next_color(){
  vec4 color;
  //---------------------------

  color = vec_color[idx_color];
  idx_color++;

  if(idx_color >= vec_color.size()) idx_color = 0;

  //---------------------------
  return color;
}
void Plot::set_time_max(int value){
  //---------------------------

  float* time_max = renderer->get_max_time();
  *time_max = float(value) / 1000;

  //---------------------------
}

}
