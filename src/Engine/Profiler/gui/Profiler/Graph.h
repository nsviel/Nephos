#pragma once

#include <Utility/Specific/Common.h>
#include <Profiler/gui/Profiler/Structure/Profiler.h>

namespace prf{class Node;}
namespace prf{class Manager;}
namespace prf::graph{class Tasker;}
namespace prf::graph{class Profiler;}
namespace prf::improfil{class Manager;}
namespace prf::gui{class Profiler;}


namespace prf::gui{

class Graph : public prf::gui::Profiler
{
public:
  //Constructor / Destructor
  Graph(prf::Node* node_profiler);
  ~Graph();

public:
  //Main function
  void show_info();
  void show_profiler(prf::graph::Profiler* profiler);

  //Draw function
  void draw_graph_command();
  void draw_graph_all(prf::graph::Profiler* profiler);
  void draw_graph_unique(prf::graph::Profiler* profiler);
  void draw_tasker_graph(prf::graph::Tasker* tasker, ImVec2 graph_dim);

  //Subfunction
  void set_graphs_max_time(int value);

  inline bool& get_pause(){return pause;}

private:
  prf::Manager* prf_manager;
  prf::graph::Tasker* selected_tasker = nullptr;
  bool pause;
  int max_time = 50;
};

}
