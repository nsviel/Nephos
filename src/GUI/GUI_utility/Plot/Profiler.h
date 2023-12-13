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
  void loop();

  //Subfunction
  void add_gpu_task(float time_beg, float time_end, string name, string color);
  void add_cpu_task(float time_beg, float time_end, string name, string color);
  uint32_t determine_color(string color);

private:
  ImProfil::Window profiler;

  vector<ImProfil::Task> vec_cpu_task;
  vector<ImProfil::Task> vec_gpu_task;
};

}
