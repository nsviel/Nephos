#pragma once

#include <Utility/GUI/Plot/Namespace.h>
#include <Utility/Specific/Common.h>

namespace prf::improfil{class Graph;}
namespace prf::graph::structure{class Task;}


namespace prf::improfil{

class Manager{
public:
  //Constructor / Destructor
  Manager(string name);
  ~Manager();

public:
  //Main function
  void render_child(ImVec2 size);
  void render_overlay(ImVec2 image_pose);
  void load_data_to_graph();
  void add_task(float ts_begin, float ts_end, string name);
  void add_task(float ts_begin, float ts_end, string name, vec4 color);
  void add_vec_task(vector<prf::graph::structure::Task> vec_task);

  //Subfunction
  vec4 get_next_color();
  void set_time_max(int value);
  void reset();

private:
  prf::improfil::Graph* graph;
  vector<prf::graph::structure::Task> vec_task;
  vector<vec4> vec_color;
  string name;
  int idx_color;
  int max_nb_data;
};

}
