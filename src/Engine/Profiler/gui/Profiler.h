#pragma once

#include <Utility/Specific/common.h>

namespace eng{class Node;}
namespace eng::render{class Node;}
namespace vk::main{class Info;}
namespace utl::improfil{class Manager;}


namespace eng::render::gui{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler(eng::Node* engine, bool* show_window);
  ~Profiler();

public:
  //Main function
  void run_panel();
  void design_panel();

  //Subfunction
  void main_info();
  void draw_graph();

  //Profiler graphs
  void draw_profiler_cpu(ImVec2 dimensions);
  void draw_profiler_gpu(ImVec2 dimensions);
  void draw_profiler_capture(ImVec2 dimensions);

private:
  utl::improfil::Manager* cpu_profiler;
  utl::improfil::Manager* gpu_profiler;
  utl::improfil::Manager* cap_profiler;
  vk::main::Info* vk_info;

  bool* show_window;
  string name;
  int width;
};

}
