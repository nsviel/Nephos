#pragma once

#include <Utility/Specific/common.h>

namespace utl::gui::serie{class Graph;}


namespace utl::gui::serie{

class Renderer{
public:
  //Constructor / Destructor
  Renderer();

public:
  //Main function
  void render_child(ImVec2 size);
  void render_overlay(ImVec2 image_pose);

  //Subfunction
  void init_color();
  vec4 get_next_color();

public:
  utl::gui::serie::Graph* graph_1;
  utl::gui::serie::Graph* graph_0;
private:
  vector<vec4> vec_color;
};

}
