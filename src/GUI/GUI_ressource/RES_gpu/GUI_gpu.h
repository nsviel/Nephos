#ifndef GUI_GPU_H
#define GUI_GPU_H

#include <ELE_specific/common.h>

class GUI;
class struct_vulkan;
class DR_ui;


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
  void render_command(VkCommandBuffer command_buffer);

private:
  struct_vulkan* vk_struct;
  DR_ui* ui_drawing;

  VkDescriptorPool imguiPool;
  ImDrawData* draw_data;
};

#endif
