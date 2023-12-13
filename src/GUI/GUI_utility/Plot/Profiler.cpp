#include "Profiler.h"


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

namespace gui::plot{

//Constructor / Destructor
Profiler::Profiler(){
  //---------------------------

  this->profiler = ImProfil::Window();
  this->max_nb_data = 100;

  //---------------------------
  this->init();
}
Profiler::~Profiler(){}

//Main function
void Profiler::init(){
  //---------------------------

  vec_color.clear();
  vec_color.push_back(ImProfil::color::turqoise);
  vec_color.push_back(ImProfil::color::greenSea);
  vec_color.push_back(ImProfil::color::emerald);
  vec_color.push_back(ImProfil::color::nephritis);
  vec_color.push_back(ImProfil::color::peterRiver);
  vec_color.push_back(ImProfil::color::belizeHole);
  vec_color.push_back(ImProfil::color::amethyst);
  vec_color.push_back(ImProfil::color::wisteria);
  vec_color.push_back(ImProfil::color::sunFlower);
  vec_color.push_back(ImProfil::color::orange);
  vec_color.push_back(ImProfil::color::carrot);
  vec_color.push_back(ImProfil::color::pumpkin);
  vec_color.push_back(ImProfil::color::alizarin);
  vec_color.push_back(ImProfil::color::pomegranate);
  vec_color.push_back(ImProfil::color::clouds);
  vec_color.push_back(ImProfil::color::silver);
  vec_color.push_back(ImProfil::color::imguiText);

  //---------------------------
}
void Profiler::loop(){
  //---------------------------

  profiler.cpu_graph->LoadFrameData(vec_cpu_task);
  profiler.gpu_graph->LoadFrameData(vec_gpu_task);

  profiler.Render();

  //---------------------------
}
void Profiler::reset(){
  //---------------------------

  this->vec_cpu_task.clear();
  this->vec_gpu_task.clear();
  this->idx_color = 0;

  //---------------------------
}

//Subfunction
void Profiler::add_cpu_task(float time_beg, float time_end, string name, string color_name){
  //---------------------------

  ImProfil::Graph_task graph_task;
  uint32_t color = determine_color(color_name);
  graph_task = {time_beg, time_end, name, color};
  vec_cpu_task.push_back(graph_task);
  if(vec_cpu_task.size() > max_nb_data) vec_cpu_task.erase(vec_cpu_task.begin());

  //---------------------------
}
void Profiler::add_cpu_task(float time_beg, float time_end, string name){
  //---------------------------

  ImProfil::Graph_task graph_task;
  uint32_t color = next_color();
  graph_task = {time_beg, time_end, name, color};
  vec_cpu_task.push_back(graph_task);
  if(vec_cpu_task.size() > max_nb_data) vec_cpu_task.erase(vec_cpu_task.begin());

  //---------------------------
}
void Profiler::add_gpu_task(float time_beg, float time_end, string name, string color_name){
  //---------------------------

  ImProfil::Graph_task graph_task;
  uint32_t color = determine_color(color_name);
  graph_task = {time_beg, time_end, name, color};
  vec_gpu_task.push_back(graph_task);
  if(vec_gpu_task.size() > max_nb_data) vec_gpu_task.erase(vec_gpu_task.begin());

  //---------------------------
}
void Profiler::add_gpu_task(float time_beg, float time_end, string name){
  //---------------------------

  ImProfil::Graph_task graph_task;
  uint32_t color = next_color();
  graph_task = {time_beg, time_end, name, color};
  vec_gpu_task.push_back(graph_task);
  if(vec_gpu_task.size() > max_nb_data) vec_gpu_task.erase(vec_gpu_task.begin());

  //---------------------------
}
uint32_t Profiler::determine_color(string color_name){
  uint32_t color;
  //---------------------------

  if(color_name == "turquoise"){
    color = ImProfil::color::turqoise;
  }
  else if(color_name == "greenSea"){
    color = ImProfil::color::greenSea;
  }
  else if(color_name == "emerald"){
    color = ImProfil::color::emerald;
  }
  else if(color_name == "nephritis"){
    color = ImProfil::color::nephritis;
  }
  else if(color_name == "peterRiver"){
    color = ImProfil::color::nephritis;
  }
  else if(color_name == "belizeHole"){
    color = ImProfil::color::nephritis;
  }
  else if(color_name == "amethyst"){
    color = ImProfil::color::amethyst;
  }
  else if(color_name == "wisteria"){
    color = ImProfil::color::wisteria;
  }
  else if(color_name == "sunFlower"){
    color = ImProfil::color::sunFlower;
  }
  else if(color_name == "orange"){
    color = ImProfil::color::orange;
  }
  else if(color_name == "carrot"){
    color = ImProfil::color::carrot;
  }
  else if(color_name == "pumpkin"){
    color = ImProfil::color::pumpkin;
  }
  else if(color_name == "alizarin"){
    color = ImProfil::color::alizarin;
  }
  else if(color_name == "pomegranate"){
    color = ImProfil::color::pomegranate;
  }
  else if(color_name == "clouds"){
    color = ImProfil::color::clouds;
  }
  else if(color_name == "silver"){
    color = ImProfil::color::silver;
  }
  else if(color_name == "imguiText"){
    color = ImProfil::color::imguiText;
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
