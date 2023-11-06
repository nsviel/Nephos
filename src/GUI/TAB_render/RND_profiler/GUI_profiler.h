#ifndef GUI_TIMING_H
#define GUI_TIMING_H

#include <RES_base/BASE_panel.h>
#include <ELE_specific/common.h>

class GUI;
class VK_info;


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
  VK_info* vk_info;
  Timer timer;

  int width;
};

#endif
