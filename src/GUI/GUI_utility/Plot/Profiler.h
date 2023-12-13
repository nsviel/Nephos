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
  void design_profiling();

private:
  ImGuiUtils::ProfilersWindow win;
};

}
