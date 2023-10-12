#ifndef GUI_TIMING_H
#define GUI_TIMING_H

#include <Specific/common.h>

class GUI;

class VK_engine;
class VK_struct;


class GUI_timing
{
public:
  //Constructor / Destructor
  GUI_timing(GUI* gui);
  ~GUI_timing();

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
