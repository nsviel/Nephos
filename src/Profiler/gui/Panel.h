#pragma once

#include <Utility/Specific/common.h>

namespace prf{class Node;}
namespace prf{class Manager;}
namespace prf{class Tasker;}
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
  void draw_graph();

  //Profiler 
  void draw_tasker_graph(prf::Tasker* tasker, ImVec2 graph_dim);
  void draw_profiler_cpu(ImVec2 graph_dim);
  void draw_profiler_gpu(ImVec2 graph_dim);
  void draw_profiler_capture(ImVec2 graph_dim);
  void draw_profiler_vulkan(ImVec2 graph_dim);

private:
  prf::Manager* prf_manager;
  prf::vulkan::Manager* prf_vulkan;
  prf::Tasker* tasker_cpu;
  prf::Tasker* tasker_gpu;
  prf::Tasker* tasker_cap;
  prf::improfil::Manager* gui_cpu;
  prf::improfil::Manager* gui_gpu;
  prf::improfil::Manager* gui_capture;

  vector<prf::improfil::Manager*> vec_graph;
  bool* show_window;
  string name;
  bool pause;
  int max_time = 50;
  int width;
};

}
