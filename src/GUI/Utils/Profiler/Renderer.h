#pragma once

#include <Utility/Specific/common.h>


namespace ImProfil{
class Graph;


class Renderer{
public:
  Renderer();

  //Main function
  void init_graph();
  void render_window();
  void render_overlay(ImVec2 image_pose);

  //Subfunction
  void display_option();

  ImProfil::Graph* graph_cpu;
  ImProfil::Graph* graph_gpu;
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
