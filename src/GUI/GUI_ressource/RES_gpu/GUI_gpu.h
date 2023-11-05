#ifndef GUI_GPU_H
#define GUI_GPU_H

#include <ELE_specific/common.h>

class GUI;
class Struct_vulkan;
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
  Struct_vulkan* struct_vulkan;

  VkDescriptorPool imguiPool;
  ImDrawData* draw_data;
};

#endif
