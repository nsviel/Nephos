#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::render{class Node;}
namespace vk::main{class Info;}
namespace utl::gui::plot{class TimeSerie;}


namespace eng::render::gui{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler(eng::render::Node* node_render, bool* show_window);
  ~Profiler();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void device_model();
  void main_loop_fps();
  void draw_graphs();

  void draw_graph();

private:
  utl::gui::plot::TimeSerie* gui_plot;
  vk::main::Info* vk_info;

  bool* show_window;
  string name;
  int width;
};

}
