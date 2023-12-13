#pragma once

#include "Namespace.h"
#include "Graph.h"
#include "Color.h"
#include "../core/imgui.h"

#include <array>
#include <map>
#include <vector>
#include <iostream>
#include <chrono>


namespace ImProfil{
class Graph;


class Window{
public:
  Window();
  void Render();

  bool stopProfiling;
  int frameOffset;
  ImProfil::Graph* cpuGraph;
  ImProfil::Graph* gpuGraph;
  int frame_width;
  int frame_spacing;
  bool use_colored_legend_text;
  using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
  TimePoint prevFpsFrameTime;
  size_t fpsFramesCount;
  float avgFrameTime;
};

}
