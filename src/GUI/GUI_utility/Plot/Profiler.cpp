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
}
Profiler::~Profiler(){}

//Main function
void Profiler::loop(){
  //---------------------------

  profiler.cpuGraph.LoadFrameData(vec_cpu_task);
  profiler.gpuGraph.LoadFrameData(vec_gpu_task);

  profiler.Render();

  //---------------------------
}

//Subfunction
void Profiler::add_cpu_task(float time_beg, float time_end, string name, string color_name){
  //---------------------------

  ImProfil::Task task;
  uint32_t color = determine_color(color_name);
  task = {time_beg, time_end, name, color};
  vec_cpu_task.push_back(task);
  if(vec_cpu_task.size() > max_nb_data) vec_cpu_task.erase(vec_cpu_task.begin());

  //---------------------------
}
void Profiler::add_gpu_task(float time_beg, float time_end, string name, string color_name){
  //---------------------------

  ImProfil::Task task;
  uint32_t color = determine_color(color_name);
  task = {time_beg, time_end, name, color};
  vec_gpu_task.push_back(task);
  if(vec_gpu_task.size() > max_nb_data) vec_gpu_task.erase(vec_gpu_task.begin());

  //---------------------------
}
uint32_t Profiler::determine_color(string color_name){
  uint32_t color;
  //---------------------------

  if(color_name == "turquoise"){
    color = ImProfil::Colors::turqoise;
  }
  else if(color_name == "greenSea"){
    color = ImProfil::Colors::greenSea;
  }
  else if(color_name == "emerald"){
    color = ImProfil::Colors::emerald;
  }
  else if(color_name == "nephritis"){
    color = ImProfil::Colors::nephritis;
  }
  else if(color_name == "peterRiver"){
    color = ImProfil::Colors::nephritis;
  }
  else if(color_name == "belizeHole"){
    color = ImProfil::Colors::nephritis;
  }
  else if(color_name == "amethyst"){
    color = ImProfil::Colors::amethyst;
  }
  else if(color_name == "wisteria"){
    color = ImProfil::Colors::wisteria;
  }
  else if(color_name == "sunFlower"){
    color = ImProfil::Colors::sunFlower;
  }
  else if(color_name == "orange"){
    color = ImProfil::Colors::orange;
  }
  else if(color_name == "carrot"){
    color = ImProfil::Colors::carrot;
  }
  else if(color_name == "pumpkin"){
    color = ImProfil::Colors::pumpkin;
  }
  else if(color_name == "alizarin"){
    color = ImProfil::Colors::alizarin;
  }
  else if(color_name == "pomegranate"){
    color = ImProfil::Colors::pomegranate;
  }
  else if(color_name == "clouds"){
    color = ImProfil::Colors::clouds;
  }
  else if(color_name == "silver"){
    color = ImProfil::Colors::silver;
  }
  else if(color_name == "imguiText"){
    color = ImProfil::Colors::imguiText;
  }


  //---------------------------
  return color;
}

}
