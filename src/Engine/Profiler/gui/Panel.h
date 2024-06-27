#pragma once

#include <string>

namespace prf{class Node;}
namespace prf{class Manager;}
namespace prf::base{class Profiler;}
namespace prf::graph{class Tasker;}
namespace prf::graph{class Profiler;}
namespace utl::improfil{class Manager;}
namespace prf::hardware{class Profiler;}
namespace prf::gui{class Profiler;}
namespace prf::gui{class Graph;}
namespace prf::gui::hardware{class Tab;}


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
  void draw_tab_profiler();
  void draw_profiler(prf::base::Profiler* profiler);

private:
  prf::Manager* prf_manager;
  prf::gui::Graph* gui_graph;
  prf::gui::hardware::Tab* gui_hardware;

  std::string gpu = "";
  std::string name;
  bool* show_window;
  int width;
};

}
