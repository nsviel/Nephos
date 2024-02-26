#pragma once

#include <Utility/Specific/common.h>

namespace prf{class Node;}
namespace prf{class Manager;}
namespace prf::graph{class Tasker;}
namespace prf::graph{class Profiler;}
namespace prf::improfil{class Manager;}


namespace prf::gui{

class Graph
{
public:
  //Constructor / Destructor
  Graph(prf::Node* node_profiler);
  ~Graph();

public:
  //Main function
  void draw_profiler(prf::graph::Profiler* profiler);

  //Subfunction
  void draw_graph_all(prf::graph::Profiler* profiler);
  void draw_graph_unique(prf::graph::Profiler* profiler);
  void draw_tasker_graph(prf::graph::Tasker* tasker, ImVec2 graph_dim);

private:
  prf::Manager* prf_manager;
  prf::graph::Tasker* selected_tasker;
};

}
