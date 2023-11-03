#ifndef GUI_ENGINE_H
#define GUI_ENGINE_H

#include <ELE_specific/common.h>

class GUI;
class struct_vulkan;
class RND_control;


class RND_engine
{
public:
  //Constructor / Destructor
  RND_engine(GUI* gui);
  ~RND_engine();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void engine_window();
  void engine_menubar();

private:
  struct_vulkan* vk_struct;
  RND_control* gui_control;

  VkDescriptorSet descriptor;
  bool has_been_initialized;
};

#endif
