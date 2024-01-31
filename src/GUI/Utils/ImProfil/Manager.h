#pragma once

#include <GUI/Utils/ImProfil/Namespace.h>
#include <Utility/Specific/common.h>

namespace utl::improfil{class Graph;}


namespace utl::improfil{

class Manager{
public:
  //Constructor / Destructor
  Manager(string name);
  ~Manager();

public:
  //Main function
  void render_child(ImVec2 size);
  void render_overlay(ImVec2 image_pose);
  void add_task(float time_beg, float time_end, string name);

  //Subfunction
  void init_color();
  vec4 get_next_color();
  void reset();

private:
  utl::improfil::Graph* graph;
  vector<utl::improfil::Task> vec_task;
  vector<vec4> vec_color;
  string name;
  int idx_color;
  int max_nb_data;
};

}
