#pragma once

#include <Utility/Specific/common.h>
#include <imgui/profiler/ImProfil.h>


namespace gui::plot{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler();
  ~Profiler();

public:
  //Main function
  void init();
  void loop();

  //Subfunction
  void add_cpu_task(float time_beg, float time_end, string name, string color);
  void add_cpu_task(ImProfil::Task task);
  void add_gpu_task(float time_beg, float time_end, string name, string color);
  void add_gpu_task(ImProfil::Task task);
  uint32_t determine_color(string color);
  uint32_t next_color();

private:
  ImProfil::Window profiler;

  vector<ImProfil::Graph_task> vec_cpu_task;
  vector<ImProfil::Graph_task> vec_gpu_task;
  vector<uint32_t> vec_color;
  int max_nb_data;
};

}
