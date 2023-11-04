#ifndef GUI_PROFILING_H
#define GUI_PROFILING_H

#include <ELE_specific/common.h>
#include <imgui/profiler/ImGuiProfilerRenderer.h>

class GUI;


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
  Timer timer;

  int width;
  ImGuiUtils::ProfilersWindow* profiler;
};

#endif
