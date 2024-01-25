#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

namespace eng{class Node;}
class VK_info;


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

  //Graph
  void engine_render_graph();

  //Text
  void engine_text_info();
  void device_model();
  bool time_update();
  void time_drawig(bool update);
  void time_general(bool update);

private:
  //utl::gui::plot::Profiler* profiler;
  VK_info* vk_info;
  Timer timer;

  bool* show_window;
  string name;
  int width;
};

}
