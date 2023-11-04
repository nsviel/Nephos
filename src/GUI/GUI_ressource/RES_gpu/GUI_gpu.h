#ifndef GUI_GPU_H
#define GUI_GPU_H

#include <ELE_specific/common.h>

class GUI;
class Struct_vulkan;
class DR_ui;
class VK_engine;


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
  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
  DR_ui* ui_drawing;

  VkDescriptorPool imguiPool;
  ImDrawData* draw_data;
};

#endif
