#ifndef GUI_ENGINE_H
#define GUI_ENGINE_H

#include <Specific/common.h>

class GUI;
class VK_struct;
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
  VK_struct* vk_struct;
  RND_control* gui_control;

  VkDescriptorSet descriptor;
  bool has_been_initialized;
};

#endif
