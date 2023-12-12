#pragma once

#include <GUI/GUI_utility/Base/Namespace.h>
#include <GUI/GUI_utility/Plot/Namespace.h>
#include <Utility/Specific/common.h>

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

  //Subfunctions
  void design_profiling();
  void device_model();
  bool time_update();
  void time_drawig(bool update);
  void time_general(bool update);

private:
  GUI* gui;
  gui::plot::Plotting* gui_plot;
  VK_info* vk_info;
  Timer timer;

  int width;
};

}
