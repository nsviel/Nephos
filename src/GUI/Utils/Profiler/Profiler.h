#pragma once

#include <GUI/Utils/Profiler/Namespace.h>
#include <Utility/Specific/common.h>

namespace profiler::gui{class Renderer;}
namespace profiler::gui{class Graph_task;}


namespace utl::gui::plot{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler();
  ~Profiler();

public:
  //Main function
  void init();
  void loop_overlay(ImVec2 image_pose);
  void loop_window();
  void reset();

  //Subfunction
  void add_task(float time_beg, float time_end, string name, string color);
  void add_task(float time_beg, float time_end, string name);
  uint32_t determine_color(string color);
  uint32_t next_color();

private:
  profiler::gui::Renderer renderer;

  vector<profiler::gui::Graph_task> vec_task;
  vector<uint32_t> vec_color;
  int max_nb_data;
  int idx_color;
};

}
