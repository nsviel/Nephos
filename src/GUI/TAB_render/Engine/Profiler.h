#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <GUI/GUI_utility/Plot/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Function/Timer/fct_timer.h>

class GUI;
class VK_info;


namespace gui::engine{

class Profiler : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Profiler(GUI* gui, bool* show_window, string name);
  ~Profiler();

public:
  //Main function
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
  GUI* gui;
  gui::plot::Profiler* profiler;
  VK_info* vk_info;
  Timer timer;

  int width;
};

}
