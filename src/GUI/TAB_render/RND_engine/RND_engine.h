#ifndef GUI_ENGINE_H
#define GUI_ENGINE_H

#include <ELE_specific/common.h>

class GUI;
class RND_control;
class VK_engine;


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
  void engine_control();

private:
  VK_engine* vk_engine;
  RND_control* gui_control;

  VkDescriptorSet descriptor;
  bool has_been_initialized;
};

#endif
