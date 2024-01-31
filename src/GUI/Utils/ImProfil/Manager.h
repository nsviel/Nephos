#pragma once

#include <GUI/Utils/ImProfil/Namespace.h>
#include <Utility/Specific/common.h>

namespace utl::improfil{class Graph;}


namespace utl::improfil{

class Manager{
public:
  //Constructor / Destructor
  Manager();

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
  utl::improfil::Graph* graph_1;
  utl::improfil::Graph* graph_0;
private:
  vector<utl::improfil::Task> vec_task;
  vector<vec4> vec_color;
  int idx_color;
    int max_nb_data;
};

}
