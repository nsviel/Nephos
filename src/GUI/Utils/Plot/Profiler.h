#pragma once

#include <GUI/Utils/TimeSerie/Namespace.h>
#include <Utility/Specific/common.h>

namespace utl::gui::serie{class Renderer;}
namespace utl::gui::serie{class Graph_task;}


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
  void add_task(float time_beg, float time_end, string name);
  uint32_t next_color();

private:
  utl::gui::serie::Renderer renderer;

  vector<utl::gui::serie::Graph_task> vec_task;
  vector<uint32_t> vec_color;
  int max_nb_data;
  int idx_color;
};

}
