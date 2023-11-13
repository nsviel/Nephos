#ifndef GUI_GPU_H
#define GUI_GPU_H

#include <UTL_specific/common.h>

class GUI;
class VK_imgui;


class GUI_gpu
{
public:
  //Constructor / Destructor
  GUI_gpu(GUI* gui);
  ~GUI_gpu();

public:
  //Main function
  void init_gui_vulkan();
  void clean_gui_vulkan();

  //Render functions
  void render_frame();

private:
  VK_imgui* vk_imgui;
};

#endif
