#ifndef VK_DRAWING_H
#define VK_DRAWING_H

#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_renderpass.h>
#include <VK_struct/Struct_command.h>
#include <VK_struct/Struct_entity.h>
#include <ELE_specific/common.h>

class Struct_vulkan;
class VK_presentation;
class VK_render;


class VK_drawing
{
public:
  //Constructor / Destructor
  VK_drawing(Struct_vulkan* struct_vulkan);
  ~VK_drawing();

public:
  //Main functions
  void draw_frame();
  void draw_frame_headless();
  void draw_frame_presentation();

  //Draw command
  void cmd_draw_data(VkCommandBuffer& command_buffer, Struct_entity* data);
  void cmd_line_with(VkCommandBuffer& command_buffer, Struct_entity* data);

private:
  Struct_vulkan* struct_vulkan;
  VK_presentation* vk_presentation;
  VK_render* vk_render;

  Timer timer;
};

#endif
