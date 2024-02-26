#pragma once

#include <Utility/Specific/common.h>

namespace prf{class Node;}
namespace prf{class Manager;}
namespace prf::graph{class Tasker;}
namespace prf::graph{class Profiler;}
namespace prf::improfil{class Manager;}
namespace prf::vulkan{class Profiler;}
namespace prf::gui{class Vulkan;}


namespace prf::gui{

class Panel
{
public:
  //Constructor / Destructor
  Panel(prf::Node* node_profiler, bool* show_window);
  ~Panel();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void main_info();
  void main_button();
  void draw_profiler();

  //Graph subfunction
  void draw_graph(prf::graph::Profiler* profiler);
  void draw_graph_all(prf::graph::Profiler* profiler);
  void draw_graph_unique(prf::graph::Profiler* profiler);

  //Profiler
  void draw_tasker_graph(prf::graph::Tasker* tasker, ImVec2 graph_dim);
  void set_graphs_max_time(int& value);

private:
  prf::Manager* prf_manager;
  prf::graph::Tasker* selected_tasker;
  prf::gui::Vulkan* gui_vulkan;

  bool* show_window;
  string gpu = "";
  string name;
  bool pause;
  int max_time = 50;
  int width;
};

}
