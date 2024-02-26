#pragma once

#include <Utility/Specific/common.h>

namespace prf{class Node;}
namespace prf{class Manager;}
namespace prf::graph{class Tasker;}
namespace prf::graph{class Profiler;}
namespace prf::improfil{class Manager;}
namespace prf::vulkan{class Profiler;}
namespace prf::gui{class Vulkan;}
namespace prf::gui{class Graph;}


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
  void set_graphs_max_time(int& value);

private:
  prf::Manager* prf_manager;
  prf::graph::Tasker* selected_tasker;
  prf::gui::Vulkan* gui_vulkan;
  prf::gui::Graph* gui_graph;

  bool* show_window;
  string gpu = "";
  string name;
  bool pause;
  int max_time = 50;
  int width;
};

}
