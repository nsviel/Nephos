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
  void init_graph();
  void render_window(ImVec2 size);
  void render_overlay(ImVec2 image_pose);

public:
  utl::gui::serie::Graph* graph;

private:
  int frame_offset;
  int frame_width;
  int frame_spacing;
  int legend_width;
  int max_graph_height;
};

}
