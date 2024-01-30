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
  vec_color.push_back(utl::gui::serie::color::turqoise);
  vec_color.push_back(utl::gui::serie::color::greenSea);
  vec_color.push_back(utl::gui::serie::color::emerald);
  vec_color.push_back(utl::gui::serie::color::nephritis);
  vec_color.push_back(utl::gui::serie::color::peterRiver);
  vec_color.push_back(utl::gui::serie::color::belizeHole);
  vec_color.push_back(utl::gui::serie::color::amethyst);
  vec_color.push_back(utl::gui::serie::color::wisteria);
  vec_color.push_back(utl::gui::serie::color::sunFlower);
  vec_color.push_back(utl::gui::serie::color::orange);
  vec_color.push_back(utl::gui::serie::color::carrot);
  vec_color.push_back(utl::gui::serie::color::pumpkin);
  vec_color.push_back(utl::gui::serie::color::alizarin);
  vec_color.push_back(utl::gui::serie::color::pomegranate);
  vec_color.push_back(utl::gui::serie::color::clouds);
  vec_color.push_back(utl::gui::serie::color::silver);
  vec_color.push_back(utl::gui::serie::color::imguiText);

  //---------------------------
}
void Profiler::loop_overlay(ImVec2 image_pose){
  //---------------------------

  renderer.graph_cpu->load_frame_data(vec_task);
  renderer.render_overlay(image_pose);

  //---------------------------
}
void Profiler::loop_window(){
  //---------------------------

  renderer.graph_cpu->load_frame_data(vec_task);
  renderer.graph_gpu->load_frame_data(vec_task);
  renderer.render_window();

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

  utl::gui::serie::Graph_task graph_task;
  uint32_t color = next_color();
  graph_task = {time_beg, time_end, name, color};
  vec_task.push_back(graph_task);
  if(vec_task.size() > max_nb_data) vec_task.erase(vec_task.begin());

  //---------------------------
}
uint32_t Profiler::next_color(){
  uint32_t color;
  //---------------------------

  color = vec_color[idx_color];
  idx_color++;

  if(idx_color >= vec_color.size()) idx_color = 0;

  //---------------------------
  return color;
}

}
