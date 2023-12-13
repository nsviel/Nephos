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

  //Main function
  void Render_window();
  void Render_overlay(ImVec2 image_pose);

  //Subfunction
  void init_graph();
  void fps_counter();
  void display_option();

  ImProfil::Graph* graph;
  using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
  TimePoint prev_fps_frame_time;
  size_t fps_frames_count;
  float avg_frame_time;
  bool use_colored_legend_text;
  bool stop_profiling;
  int frame_offset;
  int frame_width;
  int frame_spacing;
  int legend_width;
  int max_graph_height;
};

}
