#pragma once

#include <Utility/Specific/common.h>
#include <imgui/profiler/ImGuiProfilerRenderer.h>


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
  void add_cpu_task(float time_beg, float time_end, string name);
  void add_gpu_task(float time_beg, float time_end, string name, string color);
  void add_gpu_task(float time_beg, float time_end, string name);
  uint32_t determine_color(string color);
  uint32_t next_color();

private:
  ImProfil::Window profiler;

  vector<ImProfil::Task> vec_cpu_task;
  vector<ImProfil::Task> vec_gpu_task;
  vector<uint32_t> vec_color;
  int max_nb_data;
};

}
