#ifndef VK_DRAWING_H
#define VK_DRAWING_H

#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_command.h>
#include <VK_struct/Struct_data.h>
#include <ELE_specific/common.h>

class Struct_vulkan;
class Struct_synchro;
class VK_engine;
class VK_command;
class VK_descriptor;
class VK_swapchain;
class VK_viewport;
class VK_submit;


class VK_drawing
{
public:
  //Constructor / Destructor
  VK_drawing(VK_engine* vk_engine);
  ~VK_drawing();

public:
  //Main functions
  void draw_frame();
  void cmd_draw_data(Struct_subpass* subpass, Struct_data* data);
  void cmd_line_with(Struct_subpass* subpass, Struct_data* data);

private:
  Struct_vulkan* struct_vulkan;
  Struct_synchro* struct_synchro;
  VK_command* vk_command;
  VK_descriptor* vk_descriptor;
  VK_viewport* vk_viewport;
  VK_submit* vk_submit;
  VK_swapchain* vk_swapchain;
  Timer timer;
};

#endif
