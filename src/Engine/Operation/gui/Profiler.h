#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::ope{class Node;}
namespace eng::render{class Node;}
namespace vk::main{class Info;}
namespace utl{class Node;}
namespace utl::improfil{class Manager;}


namespace eng::render::gui{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler(eng::ope::Node* node_operation, bool* show_window);
  ~Profiler();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void main_info();
  void main_button();
  void draw_graph();
  void draw_timeline();

  //Profiler graphs
  void draw_profiler_cpu(ImVec2 dimensions);
  void draw_profiler_gpu(ImVec2 dimensions);
  void draw_profiler_capture(ImVec2 dimensions);

private:
  eng::Node* node_engine;
  utl::Node* node_utility;
  utl::improfil::Manager* gui_cpu;
  utl::improfil::Manager* gui_gpu;
  utl::improfil::Manager* gui_capture;
  vk::main::Info* vk_info;

  bool* show_window;
  string name;
  bool pause;
  int max_time = 50;
  int width;
};

}
