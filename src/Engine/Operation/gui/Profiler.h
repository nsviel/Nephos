#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

namespace eng{class Node;}
namespace vk::main{class Info;}
namespace utl::gui::plot{class Profiler;}


namespace eng::ope::gui{

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
  void device_model();
  void main_loop_fps();
  void draw_cpu_graph();



  void engine_text_info();
  void time_drawig(bool update);


private:
  utl::gui::plot::Profiler* profiler;
  vk::main::Info* vk_info;
  Timer timer;

  bool* show_window;
  string name;
  int width;
};

}
