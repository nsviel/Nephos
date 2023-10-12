#ifndef GUI_GPU_H
#define GUI_GPU_H

#include <Specific/common.h>

class Engine;
class VK_struct;
class DR_ui;


class GUI_gpu
{
public:
  //Constructor / Destructor
  GUI_gpu(Engine* engine);
  ~GUI_gpu();

public:
  //Clean functions
  void clean_gui();

  //Init function
  void init_gui();
  void gui_vulkan();
  void gui_select_font();
  void gui_load_font();

  //Render functions
  void render_frame();
  void render_command(VkCommandBuffer command_buffer);

private:
  VK_struct* vk_struct;
  DR_ui* ui_drawing;

  VkDescriptorPool imguiPool;
  ImDrawData* draw_data;
};

#endif
