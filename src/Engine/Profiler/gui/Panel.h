#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace prf{class Manager;}
namespace prf{class Structure;}
namespace prf::graph{class Tasker;}
namespace prf::graph{class Profiler;}
namespace prf::improfil{class Manager;}
namespace prf::vulkan{class Profiler;}
namespace prf::gui{class Profiler;}
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

private:
  prf::Manager* prf_manager;
  prf::gui::Profiler* selected_profiler = nullptr;
  prf::gui::Vulkan* gui_vulkan;
  prf::gui::Graph* gui_graph;

  bool* show_window;
  string gpu = "";
  string name;
  int max_time = 50;
  int width;
};

}
