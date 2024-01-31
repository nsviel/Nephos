#pragma once

#include <GUI/Utils/TimeSerie/Namespace.h>
#include <Utility/Specific/common.h>

namespace utl::gui::serie{class Renderer;}
namespace utl::gui::serie{class Task;}


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
  vec4 next_color();

private:
  utl::gui::serie::Renderer renderer;

  vector<utl::gui::serie::Task> vec_task;
  vector<vec4> vec_color;
  int max_nb_data;
  int idx_color;
};

}
