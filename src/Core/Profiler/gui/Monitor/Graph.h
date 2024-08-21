#pragma once

#include <imgui/core/imgui.h>

namespace prf{class Node;}
namespace prf{class Structure;}
namespace prf::monitor{class Profiler;}
namespace prf::monitor{class Tasker;}


namespace prf::gui::dynamic{

class Graph
{
public:
  //Constructor / Destructor
  Graph(prf::Node* node_profiler);
  ~Graph();

public:
  //Main function
  void draw_profiler(prf::monitor::Profiler* profiler);

  //Graph function
  void draw_info();
  void draw_tasker_all(prf::monitor::Profiler* profiler);
  void draw_tasker_separated(prf::monitor::Profiler* profiler);

  //Subfunction
  void draw_tasker_graph(prf::monitor::Tasker* tasker, ImVec2 dimension, bool pause);
  void draw_graph_command(ImVec2 dimension, ImVec2 pose);

private:
  prf::Structure* prf_struct;
  prf::monitor::Tasker* current_tasker = nullptr;
};

}
