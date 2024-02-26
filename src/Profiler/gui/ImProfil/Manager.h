#pragma once

#include <GUI/Plot/Namespace.h>
#include <Utility/Specific/common.h>

namespace prf::improfil{class Graph;}
namespace prf::graph{class Task;}


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
  void add_task(float time_beg, float time_end, string name);
  void add_task(float time_beg, float time_end, string name, vec4 color);
  void add_vec_task(vector<prf::graph::Task> vec_task);

  //Subfunction
  vec4 get_next_color();
  void set_time_max(int value);
  void reset();

private:
  prf::improfil::Graph* graph;
  vector<prf::graph::Task> vec_task;
  vector<vec4> vec_color;
  string name;
  int idx_color;
  int max_nb_data;
};

}
