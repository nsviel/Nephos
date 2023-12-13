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

  ImProfil::Graph* cpu_graph;
  ImProfil::Graph* gpu_graph;

  using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
  TimePoint prevFpsFrameTime;
  size_t fpsFramesCount;
  float avgFrameTime;
  bool use_colored_legend_text;
  bool stopProfiling;
  int frameOffset;
  int frame_width;
  int frame_spacing;
};

}
