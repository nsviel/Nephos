#include "Profiler.h"

#include <GUI/Utils/TimeSerie/Namespace.h>


namespace utl::gui::plot{

//Constructor / Destructor
Profiler::Profiler(){
  //---------------------------

  this->renderer = utl::gui::serie::Renderer();
  this->max_nb_data = 100;

  //---------------------------
  this->init();
}
Profiler::~Profiler(){}

//Main function
void Profiler::init(){
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
void Profiler::loop_overlay(ImVec2 image_pose){
  //---------------------------

  renderer.graph_0->load_graph_data(vec_task);
  renderer.render_overlay(image_pose);

  //---------------------------
}
void Profiler::loop_window(){
  //---------------------------

  renderer.graph_0->load_graph_data(vec_task);
  renderer.graph_1->load_graph_data(vec_task);
  ImVec2 available_size = ImGui::GetContentRegionAvail();
  available_size.y = available_size.y / 2 - 2.5;
  renderer.render_window(available_size);

  //---------------------------
}
void Profiler::reset(){
  //---------------------------

  this->vec_task.clear();
  this->vec_task.clear();
  this->idx_color = 0;

  //---------------------------
}

//Subfunction
void Profiler::add_task(float time_beg, float time_end, string name){
  //---------------------------

  utl::gui::serie::Task task;
  vec4 color = next_color();
  task = {time_beg, time_end, name, color};
  vec_task.push_back(task);
  if(vec_task.size() > max_nb_data) vec_task.erase(vec_task.begin());

  //---------------------------
}
vec4 Profiler::next_color(){
  vec4 color;
  //---------------------------

  color = vec_color[idx_color];
  idx_color++;

  if(idx_color >= vec_color.size()) idx_color = 0;

  //---------------------------
  return color;
}

}
