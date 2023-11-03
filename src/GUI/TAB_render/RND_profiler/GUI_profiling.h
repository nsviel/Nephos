#ifndef GUI_PROFILING_H
#define GUI_PROFILING_H

#include <ELE_specific/common.h>
#include <imgui/profiler/ImGuiProfilerRenderer.h>

class GUI;

class VK_engine;
class struct_vulkan;


class GUI_profiling
{
public:
  //Constructor / Destructor
  GUI_profiling(GUI* gui);
  ~GUI_profiling();

public:
  //Main function
  void design_panel();

  //Subfunctions
  void design_profiling();

private:
  GUI* gui;
  VK_engine* vk_engine;
  struct_vulkan* vk_struct;
  Timer timer;

  int width;
  ImGuiUtils::ProfilersWindow* profiler;
};

#endif
