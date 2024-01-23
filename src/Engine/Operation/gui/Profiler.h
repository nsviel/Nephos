#pragma once

#include <Utility/GUI/Base/Panel.h>
#include <Utility/GUI/Plot/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

class Engine;
class VK_info;


namespace gui::engine{

class Profiler
{
public:
  //Constructor / Destructor
  Profiler(Engine* engine, bool* show_window, string name);
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
  gui::plot::Profiler* profiler;
  VK_info* vk_info;
  Timer timer;

  bool* show_window;
  string name;
  int width;
};

}
