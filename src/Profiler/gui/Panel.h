#pragma once

#include <Utility/Specific/common.h>

namespace prf{class Node;}
namespace prf{class Manager;}
namespace prf{class Tasker;}
namespace prf{class Profiler;}
namespace prf::vulkan{class Manager;}
namespace prf::improfil{class Manager;}


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
  void draw_graph(prf::Profiler* profiler);
  void draw_graph_all(prf::Profiler* profiler);
  void draw_graph_unique(prf::Profiler* profiler);
  void draw_graph_vulkan(prf::vulkan::Manager* vulkan);

  //Profiler
  void draw_tasker_graph(prf::Tasker* tasker, ImVec2 graph_dim);
  void draw_profiler_vulkan(prf::vulkan::Manager* vulkan, ImVec2 graph_dim);
  void set_graphs_max_time(int& value);

private:
  prf::Manager* prf_manager;
  prf::vulkan::Manager* prf_vulkan;
  prf::Tasker* selected_tasker;

  bool* show_window;
  string gpu = "";
  string name;
  bool pause;
  int max_time = 50;
  int width;
};

}
