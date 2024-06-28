#pragma once

#include <imgui/core/imgui.h>

namespace prf{class Node;}
namespace prf{class Structure;}
namespace prf::dynamic{class Manager;}
namespace prf::dynamic{class Profiler;}
namespace prf::dynamic{class Tasker;}
namespace prf::graph{class Profiler;}
namespace utl::improfil{class Plot;}
namespace prf::gui{class Profiler;}


namespace prf::gui::dynamic{

class Graph
{
public:
  //Constructor / Destructor
  Graph(prf::Node* node_profiler);
  ~Graph();

public:
  //Main function
  void draw_profiler(prf::dynamic::Profiler* profiler);

  //Graph function
  void draw_info();
  void draw_graph_all(prf::dynamic::Profiler* profiler);
  void draw_graph_unique(prf::dynamic::Profiler* profiler);

  //Subfunction
  void draw_graph_command();
  void draw_tasker_graph(prf::dynamic::Tasker* tasker, ImVec2 graph_dim);
  void set_graphs_max_time(int value);

  inline bool& get_pause(){return pause;}

private:
  prf::Structure* prf_struct;
  prf::dynamic::Manager* prf_manager;
  prf::dynamic::Tasker* selected_tasker = nullptr;
  bool pause;
  int max_time = 50;
};

}
