#include "Plot.h"


namespace utl::improfil{

Plot::Plot(){
  //---------------------------

  this->renderer = new utl::improfil::Renderer();
  this->idx_color = 0;
  this->max_nb_data = 100;
  this->vec_color = utl::improfil::colormap::viridis;

  //---------------------------
}
Plot::Plot(std::string name){
  //---------------------------

  this->name = name;
  this->renderer = new utl::improfil::Renderer();
  this->idx_color = 0;
  this->max_nb_data = 100;
  this->vec_color = utl::improfil::colormap::viridis;

  //---------------------------
}
Plot::~Plot(){}

//Main function
void Plot::render(std::string name, ImVec2 dimension){
  std::string title = name + "##renderer";
  //---------------------------

  ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 1));
  ImGui::BeginChild(title.c_str(), ImVec2(0, dimension.y));
  renderer->render_graph(dimension);
  ImGui::End();
  ImGui::PopStyleColor();
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + dimension.y);

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

//Subfunction
glm::vec4 Plot::get_next_color(){
  glm::vec4 color;
  //---------------------------

  color = vec_color[idx_color];
  idx_color++;

  if(idx_color >= vec_color.size()) idx_color = 0;

  //---------------------------
  return color;
}
void Plot::add_task(float ts_begin, float ts_end, std::string name, glm::vec4 color){
  //---------------------------

  //Insert task
  utl::improfil::Task task;
  task.ts_begin = ts_begin;
  task.ts_end = ts_end;
  task.name = name;
  task.color = (color == glm::vec4(0, 0, 0, 0)) ? get_next_color() : color;
  vec_task.push_back(task);

  //Remove old one
  if(vec_task.size() > max_nb_data) vec_task.erase(vec_task.begin());

  //---------------------------
}
void Plot::set_time_max(int value){
  //---------------------------

  float* time_max = renderer->get_max_time();
  *time_max = float(value) / 1000;

  //---------------------------
}

}
