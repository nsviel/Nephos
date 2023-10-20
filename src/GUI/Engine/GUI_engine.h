#ifndef GUI_ENGINE_H
#define GUI_ENGINE_H

#include <Specific/common.h>

class GUI;
class VK_struct;
class GUI_control_engine;
class GUI_mainmenubar;

class GUI_engine
{
public:
  //Constructor / Destructor
  GUI_engine(GUI* gui);
  ~GUI_engine();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void engine_window();
  void engine_menubar();

private:
  VK_struct* vk_struct;
  GUI_control_engine* gui_control;
  GUI_mainmenubar* gui_menubar;

  VkDescriptorSet descriptor;
  bool has_been_initialized;
};

#endif
