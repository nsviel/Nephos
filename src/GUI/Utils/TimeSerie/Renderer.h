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
  void render_window(ImVec2 size);
  void render_overlay(ImVec2 image_pose);

public:
  utl::gui::serie::Graph* graph;

private:

};

}
