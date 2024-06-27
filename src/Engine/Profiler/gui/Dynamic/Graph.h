#pragma once

#include <imgui/core/imgui.h>

namespace prf{class Node;}
namespace prf{class Manager;}
namespace prf::base{class Profiler;}
namespace prf::graph{class Tasker;}
namespace prf::graph{class Profiler;}
namespace utl::improfil{class Plot;}
namespace prf::gui{class Profiler;}


namespace prf::gui{

class Graph
{
public:
  //Constructor / Destructor
  Graph(prf::Node* node_profiler);
  ~Graph();

public:
  //Main function
  void show_profiler(prf::base::Profiler* profiler);

  //Graph function
  void draw_info();
  void draw_graph_all(prf::graph::Profiler* profiler);
  void draw_graph_unique(prf::graph::Profiler* profiler);

  //Subfunction
  void draw_graph_command();
  void draw_tasker_graph(prf::graph::Tasker* tasker, ImVec2 graph_dim);
  void set_graphs_max_time(int value);

  inline bool& get_pause(){return pause;}

private:
  prf::Manager* prf_manager;
  prf::graph::Tasker* selected_tasker = nullptr;
  bool pause;
  int max_time = 50;
};

}
