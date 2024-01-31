#pragma once

#include <GUI/Utils/TimeSerie/Namespace.h>
#include <Utility/Specific/common.h>

namespace utl::gui::serie{class Graph;}


namespace utl::gui::serie{

class Renderer{
public:
  //Constructor / Destructor
  Renderer();

public:
  //Main function
  void loop_overlay(ImVec2 image_pose);
  void loop_window();
  void render_child(ImVec2 size);
  void render_overlay(ImVec2 image_pose);
  void add_task(float time_beg, float time_end, string name);

  //Subfunction
  void init_color();
  vec4 get_next_color();
  void reset();

public:
  utl::gui::serie::Graph* graph_1;
  utl::gui::serie::Graph* graph_0;
private:
  vector<utl::gui::serie::Task> vec_task;
  vector<vec4> vec_color;
  int idx_color;
    int max_nb_data;
};

}
