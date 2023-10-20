#ifndef GUI_TIMING_H
#define GUI_TIMING_H

#include <Tab/Base/BASE_panel.h>
#include <Specific/common.h>

class GUI;
class VK_engine;
class VK_struct;


class GUI_profiler : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_profiler(GUI* gui, bool* show_window, string name);
  ~GUI_profiler();

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
  VK_engine* vk_engine;
  VK_struct* vk_struct;
  Timer timer;

  int width;
};

#endif
