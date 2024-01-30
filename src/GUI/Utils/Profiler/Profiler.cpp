#include "Profiler.h"

#include <GUI/Utils/Profiler/Namespace.h>


/*
  struct Task{
    double startTime;
    double endTime;
    std::string name;
    uint32_t color;
    double GetLength(){
      return endTime - startTime;
    }
  };*/

namespace utl::gui::plot{

//Constructor / Destructor
Profiler::Profiler(){
  //---------------------------

  this->renderer = profiler::gui::Renderer();
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
  vec_color.push_back(profiler::gui::color::turqoise);
  vec_color.push_back(profiler::gui::color::greenSea);
  vec_color.push_back(profiler::gui::color::emerald);
  vec_color.push_back(profiler::gui::color::nephritis);
  vec_color.push_back(profiler::gui::color::peterRiver);
  vec_color.push_back(profiler::gui::color::belizeHole);
  vec_color.push_back(profiler::gui::color::amethyst);
  vec_color.push_back(profiler::gui::color::wisteria);
  vec_color.push_back(profiler::gui::color::sunFlower);
  vec_color.push_back(profiler::gui::color::orange);
  vec_color.push_back(profiler::gui::color::carrot);
  vec_color.push_back(profiler::gui::color::pumpkin);
  vec_color.push_back(profiler::gui::color::alizarin);
  vec_color.push_back(profiler::gui::color::pomegranate);
  vec_color.push_back(profiler::gui::color::clouds);
  vec_color.push_back(profiler::gui::color::silver);
  vec_color.push_back(profiler::gui::color::imguiText);

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
void Profiler::add_task(float time_beg, float time_end, string name, string color_name){
  //---------------------------

  profiler::gui::Graph_task graph_task;
  uint32_t color = determine_color(color_name);
  graph_task = {time_beg, time_end, name, color};
  vec_task.push_back(graph_task);
  if(vec_task.size() > max_nb_data) vec_task.erase(vec_task.begin());

  //---------------------------
}
void Profiler::add_task(float time_beg, float time_end, string name){
  //---------------------------

  profiler::gui::Graph_task graph_task;
  uint32_t color = next_color();
  graph_task = {time_beg, time_end, name, color};
  vec_task.push_back(graph_task);
  if(vec_task.size() > max_nb_data) vec_task.erase(vec_task.begin());

  //---------------------------
}
uint32_t Profiler::determine_color(string color_name){
  uint32_t color;
  //---------------------------

  if(color_name == "turquoise"){
    color = profiler::gui::color::turqoise;
  }
  else if(color_name == "greenSea"){
    color = profiler::gui::color::greenSea;
  }
  else if(color_name == "emerald"){
    color = profiler::gui::color::emerald;
  }
  else if(color_name == "nephritis"){
    color = profiler::gui::color::nephritis;
  }
  else if(color_name == "peterRiver"){
    color = profiler::gui::color::nephritis;
  }
  else if(color_name == "belizeHole"){
    color = profiler::gui::color::nephritis;
  }
  else if(color_name == "amethyst"){
    color = profiler::gui::color::amethyst;
  }
  else if(color_name == "wisteria"){
    color = profiler::gui::color::wisteria;
  }
  else if(color_name == "sunFlower"){
    color = profiler::gui::color::sunFlower;
  }
  else if(color_name == "orange"){
    color = profiler::gui::color::orange;
  }
  else if(color_name == "carrot"){
    color = profiler::gui::color::carrot;
  }
  else if(color_name == "pumpkin"){
    color = profiler::gui::color::pumpkin;
  }
  else if(color_name == "alizarin"){
    color = profiler::gui::color::alizarin;
  }
  else if(color_name == "pomegranate"){
    color = profiler::gui::color::pomegranate;
  }
  else if(color_name == "clouds"){
    color = profiler::gui::color::clouds;
  }
  else if(color_name == "silver"){
    color = profiler::gui::color::silver;
  }
  else if(color_name == "imguiText"){
    color = profiler::gui::color::imguiText;
  }


  //---------------------------
  return color;
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
